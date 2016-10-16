#include "ClientConnection.h"

#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "../utils/Logger.h"

#define CLASSNAME "ClientConnection.class"


ClientConnection::~ClientConnection() {
    close(this->clientSocket);
}

/**
 * @param clientSocket <--- socket id
 * @param server
 * @param username
 */
ClientConnection::ClientConnection(int clientSocket, Server *server, char *username) {
    this->clientSocket = clientSocket;
    this->server = server;
    strcpy(this->username, username);
    this->shouldClose = false;


    struct timeval timeout;
    timeout.tv_sec = 100;
    timeout.tv_usec = 0;

    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }

    timeout.tv_sec = 10;
    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }
}

void connectionControl(ClientConnection* handler) {
    struct event alive;
    alive.data.code = EventCode::MSG_OK;
    while (!handler->shouldClose) { // while está vivo
        sleep(5);
        handler->queuemutex.lock();
        handler->event_queue.push_front(alive);
        handler->queuemutex.unlock();
    }
}

int connectionReader(ClientConnection *handler) {
    bool isComplete;
    SocketUtils sockutils;
    vector<struct event> mensajes;
    char buffer[MSGSIZE];

    do {
        isComplete = sockutils.readSocket(handler->getClientSocket(), buffer);
        if (((*(struct event*)buffer)).data.code == EventCode::MSG_OK) { cout<<"esta vivo"<<endl;continue; }
        else {
            if (!isComplete) {
                //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
                handler->stop();
                //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
            } else {
                // TODO reveer si realmente todavía usamos un vector<struct event> mensajes, porque todos los eventos
                // de tecla son FINAL_MSG
                mensajes.push_back(*(struct event *)buffer);
                if ((*(struct event*)buffer).completion == EventCompletion::FINAL_MSG) {
                    LOGGER_WRITE(Logger::INFO, "Se recibio mensaje de " + string(handler->getUsername()) ,"ClientConnection.class")
                    cout << "Se recibio mensaje de " + string(handler->getUsername()) << endl;
                    if (mensajes.front().data.code == EventCode::SDL_KEYRIGHT_PRESSED) {
                        cout << "Llegó mensaje de tecla derecha apretada" << endl;
                    }
                    if (mensajes.front().data.code == EventCode::SDL_KEYLEFT_PRESSED) {
                        cout << "Llegó mensaje de tecla derecha apretada" << endl;
                    }
                    handler->handle_message(mensajes, mensajes.front().data.code);
                    mensajes.clear();
                }
            }
        }
    } while (isComplete and !handler->shouldClose);
    /* Si no está completo devuelvo 0 */
    return isComplete ? 1 : 0;
}

int connectionWriter(ClientConnection *data) {
    int result;
    SocketUtils sockutils;
    while (!data->shouldClose) {
        data->queuemutex.lock();
        if (data->has_events()) {
            event event = data->event_queue.front();
            data->event_queue.pop_front();
            data->queuemutex.unlock();
            result = sockutils.writeSocket(data->getClientSocket(), event);
            if (result == -1) {
                data->stop();
            }

        } else { data->queuemutex.unlock(); }
    }
    return 1;
}

void ClientConnection::start() {
    this->reader = std::thread(connectionReader, this);
    this->writer = std::thread(connectionWriter, this);
    this->control = std::thread(connectionControl, this);
}

void ClientConnection::stop() {
    LOGGER_WRITE(Logger::INFO, "Matando el client connection de " + string(username), "ClientConnection.class")
    cout << "Matando el client connection de " << username << endl;
    shouldClose = true;
    this->reader.detach();
    this->writer.detach(); /* Guarda que tiene un while true, no es join */
    this->control.detach();
    close(this->clientSocket);
}

void ClientConnection::push_event(struct event event) {
    this->queuemutex.lock();
    if (this->event_queue.size() >= 50) {
        event_queue.pop_front();
    }
    event_queue.push_back(event);
    this->queuemutex.unlock();
}

void ClientConnection::handle_message(vector<struct event> mensajes, EventCode code) {
    // MessageUtils messageutils;
    // Message* message = messageutils.buildMessage(mensajes);
    for (auto event : mensajes) {
        server->handle_message(event, code, this->getUsername());
    }
}

ClientConnection::ClientConnection() {}

char *ClientConnection::getUsername() {
    return username;
}
