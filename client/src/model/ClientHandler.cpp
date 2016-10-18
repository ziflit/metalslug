#include "ClientHandler.h"


void sendHeartbeat(ClientHandler* handler) {
	struct event alive;
	alive.data.code = EventCode::MSG_OK;
	while (!handler->shouldClose) { // while está vivo
		handler->sendEvent(alive);
		sleep(5);
	}
}

void readConfigs(ClientHandler* handler, SocketUtils& sockutils){
    int sizeGlobalConfig = sizeof(struct xmlConfig);
    cout << "tamaño struct" << sizeGlobalConfig << endl;
    char globalConfigBuffer[sizeGlobalConfig];
    bool isComplete;
    isComplete = sockutils.readSocket(handler->getClientSocket(), globalConfigBuffer, sizeGlobalConfig);
    cout << "rompio?" << isComplete <<endl;
    if(isComplete){
        struct xmlConfig xmlConf = (*(struct xmlConfig*) globalConfigBuffer);
        cout << "alto de ventana "<< xmlConf.alto << endl;
    }

}

void connectionReader(ClientHandler *handler) {
	int is_server_alive;
	bool isComplete;

	SocketUtils sockutils;
	vector<struct event> events;

	char buffer[MSGSIZE];
	char eventBuffer[MSGSIZE];

	while (!handler->shouldClose) {
//		is_server_alive = sockutils.peek(handler->getClientSocket(), buffer);
//		if (not is_server_alive and !handler->shouldClose) {
//			handler->stop();
//			break;
//		}
		isComplete = sockutils.readSocket(handler->getClientSocket(),
				eventBuffer);
    if (isComplete) {
        struct event incommingEvent = (*(struct event*) eventBuffer);
        if (incommingEvent.data.code == EventCode::MSG_OK) {
//            readConfigs(handler, sockutils);
            continue;
        }
        handler->receiveEvent(incommingEvent);
    } else {
        cout << "Mal paquete..." << endl;
        is_server_alive = recv(handler->getClientSocket(), &buffer, MSGSIZE,
                               MSG_PEEK);
        if (is_server_alive == -1) {
            LOGGER_WRITE(Logger::ERROR, "Conexion con el servidor perdida",
                         "ClientHandler.class")
                handler->stop();
        }
		}
    usleep(5000);
	}
}

int connectionWriter(ClientHandler *data) {
	int result;
	while (!data->shouldClose) {
		data->outgoingMutex.lock();
		if (data->has_events_to_send()) {
			event event = data->outgoingEvents.front();
			data->outgoingEvents.pop_front();
			data->outgoingMutex.unlock();

			SocketUtils sockutils;
			result = sockutils.writeSocket(data->getClientSocket(), event);

			if (result == -1) {
				cout << "El servidor está desconectado" << endl;
				if (!data->shouldClose) {
					data->stop();
				}
			}

		} else {
			data->outgoingMutex.unlock();
		}
		usleep(5000);
	}
	return 1;
}

ClientHandler::~ClientHandler() {
	close(this->clientSocket);
}

/**
 * @param clientSocket <--- socket id
 * @param client
 * @param username
 */
ClientHandler::ClientHandler(int clientSocket, Client *client,
		const char *username) {
	this->clientSocket = clientSocket;
	this->client = client;
	strcpy(this->username, username);
	this->shouldClose = false;
	setSocketTimeout();
}

void ClientHandler::setSocketTimeout() const {
	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
			sizeof(timeout))) {
		cout << "Error on setting timeout" << endl;
	}

	timeout.tv_sec = 10;
	if (setsockopt(clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout,
			sizeof(timeout))) {
		cout << "Error on setting timeout" << endl;
	}
}

void ClientHandler::start() {
	this->reader = std::thread(connectionReader, this);
	this->writer = std::thread(connectionWriter, this);
	this->control = std::thread(sendHeartbeat, this);
}

void ClientHandler::stop() {
	if (not shouldClose) {
		this->shouldClose = true;
		close(this->clientSocket);
		this->writer.detach(); /* Guarda que tiene un while true, no es join */
		this->reader.detach();
		this->control.detach();
		this->client->set_connection_status(false);
	}
}

void ClientHandler::receiveEvent(struct event event) {
	this->incommingMutex.lock();
	incommingEvents.push_back(event);
	this->incommingMutex.unlock();
}


void ClientHandler::sendEvent(struct event event) {
    event.data.id = client->getEntity();
    this->outgoingMutex.lock();
    outgoingEvents.push_back(event);
    this->outgoingMutex.unlock();
}

ClientHandler::ClientHandler() {
}

char *ClientHandler::getUsername() {
	return username;
}

vector<struct event> ClientHandler::getModelState() {
	//TODO caso borde: ultimo mensaje se pierde
	vector<struct event> modelState;
	bool final = false;

	this->incommingMutex.lock();
	list<struct event>::iterator it = incommingEvents.begin();
	while (it != incommingEvents.end() && !final) {
		struct event event = (*it);
    modelState.push_back(event);
    auto prev = it++;
    incommingEvents.erase(prev);
    final = event.completion == EventCompletion::FINAL_MSG;
  }
  this->incommingMutex.unlock();
  return modelState;
}
