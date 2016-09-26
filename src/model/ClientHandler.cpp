#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "ClientHandler.h"
#include "../Utils/Logger.h"

#define CLASSNAME "ClientHandler.class"


ClientHandler::~ClientHandler() {
    close(this->clientSocket);
}

/**
 * @param clientSocket <--- socket id
 * @param client
 * @param username
 */
ClientHandler::ClientHandler(int clientSocket, Client *client, const char *username) {
    this->clientSocket = clientSocket;
    this->client = client;
    strcpy(this->username, username);
    this->shouldClose = false;


    struct timeval timeout;
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;

    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }

    timeout.tv_sec = 10;
    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }
}

void connectionControl(ClientHandler* handler) {
    struct msg_request_t alive;
    alive.code = MessageCode::MSG_OK;
    while (true) { // while está vivo
        handler->push_event(alive);
        sleep(5);
    }
}

int connectionReader(ClientHandler *handler) {
    bool isComplete;
    SocketUtils sockutils;
    vector<struct msg_request_t> mensajes;
    char buffer[BUFSIZE];

    do {
        isComplete = sockutils.readSocket(handler->getClientSocket(), buffer);
        if (((*(struct msg_request_t*)buffer)).code == MessageCode::MSG_OK) { continue; }
        else {
            if (!isComplete) {
                //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
                handler->stop();
                //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
            } else {
                mensajes.push_back(*(struct msg_request_t *)buffer);
                if ((*(struct msg_request_t*)buffer).completion == MessageCompletion::FINAL_MSG) {
                    LOGGER_WRITE(Logger::INFO, "Se recibio mensaje de " + string(handler->getUsername()) ,"ClientHandler.class")
                        handler->handle_message(mensajes, mensajes.front().code);
                    mensajes.clear();
                }
            }
        }
    } while (isComplete and !handler->shouldClose);
    /* Si no está completo devuelvo 0 */
    return isComplete ? 1 : 0;
}

int connectionWriter(ClientHandler *data) {
    while (!data->shouldClose) {
        data->queuemutex.lock();
        if (data->has_events()) {
            msg_request_t event = data->event_queue.front();
            data->event_queue.pop();
            data->queuemutex.unlock();
            SocketUtils sockutils;
            sockutils.writeSocket(data->getClientSocket(), event);

        } else { data->queuemutex.unlock(); }
    }
    return 1;
}

void ClientHandler::start() {
    this->reader = std::thread(connectionReader, this);
    this->writer = std::thread(connectionWriter, this);
    this->control = std::thread(connectionControl, this);
}

void ClientHandler::stop() {
    LOGGER_WRITE(Logger::INFO, "Matando el client connection de " + string(username), "ClientHandler.class")
    cout << "Matando el client connection de " << username << endl;
    shouldClose = true;
    this->reader.detach();
    this->writer.detach(); /* Guarda que tiene un while true, no es join */
    close(this->clientSocket);
}

void ClientHandler::push_event(struct msg_request_t event) {
    this->queuemutex.lock();
    event_queue.push(event);
    this->queuemutex.unlock();
}

void ClientHandler::handle_message(vector<struct msg_request_t> mensajes, MessageCode code) {
    MessageUtils messageutils;
    Message* message = messageutils.buildMessage(mensajes);
    this->client->handle_message(message, code);
}

ClientHandler::ClientHandler() {}

char *ClientHandler::getUsername() {
    return username;
}
