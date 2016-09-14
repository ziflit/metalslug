#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "ClientConnection.h"
#include "../Utils/Logger.h"

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
    timeout.tv_sec = 10000;
    timeout.tv_usec = 0;

    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }


    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }
}

int connectionReader(ClientConnection *handler) {
    bool isComplete;
    SocketUtils sockutils;
    vector<struct msg_request_t> mensajes;
    char buffer[BUFSIZE];

    do {
        isComplete = sockutils.readSocket(handler->getClientSocket(), buffer);

        if (!isComplete) {
            //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
            handler->stop();
            //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
        } else {
            mensajes.push_back(*(struct msg_request_t *)buffer);
            if ((*(struct msg_request_t*)buffer).completion == MessageCompletion::FINAL_MSG) {
                LOGGER_WRITE(Logger::INFO, "Se recibio mensaje de " + string(handler->getUsername()) ,"ClientConnection.class")
                handler->handle_message(mensajes, mensajes.front().code);
                mensajes.clear();
            }
        }
    } while (isComplete and !handler->shouldClose);
    /* Si no está completo devuelvo 0 */
    return isComplete ? 1 : 0;
}

int connectionWriter(ClientConnection *data) {
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

void ClientConnection::start() {
    this->reader = std::thread(connectionReader, this);
    this->writer = std::thread(connectionWriter, this);
}

void ClientConnection::stop() {
    LOGGER_WRITE(Logger::INFO, "Matando el client connection de " + string(username), "ClientConnection.class")
    cout << "Matando el client connection de " << username << endl;
    shouldClose = true;
    this->reader.detach();
    this->writer.detach(); /* Guarda que tiene un while true, no es join */
    close(this->clientSocket);
}

void ClientConnection::push_event(struct msg_request_t event) {
    this->queuemutex.lock();
    event_queue.push(event);
    this->queuemutex.unlock();
}

void ClientConnection::handle_message(vector<struct msg_request_t> mensajes, MessageCode code) {
    MessageUtils messageutils;
    Message* message = messageutils.buildMessage(mensajes);
    server->handle_message(message, code);
}

ClientConnection::ClientConnection() {}

char *ClientConnection::getUsername() {
    return username;
}
