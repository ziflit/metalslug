
#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "ClientConnection.h"
#include "../Utils/Logger.h"
#include <string.h>
#include "../Utils/SocketUtils.h"

#define CLASSNAME "ClientConnection.class"


ClientConnection::~ClientConnection() {
    close(this->clientSocket);
}

/**
 *
 * @param clientSocket <--- socket id
 * @param server
 * @param id   <--- client id
 * @param username
 * @return
 */

ClientConnection::ClientConnection(int clientSocket, Server *server, char* username) {
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
    struct msg_request_t *message;
    char buffer[BUFSIZE];

    do {
        isComplete = sockutils.readSocket(handler->getClientSocket(), buffer);

        if (!isComplete) {
            //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
            handler->stop();
            //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
        } else {
            message = (struct msg_request_t *) buffer;
            handler->handle_message(*message);
        }
    } while (isComplete and !handler->shouldClose);
    /* Si no está completo devuelvo 0 */
    return isComplete ? 1 : 0;
}

int connectionWriter(ClientConnection* data) {
    while (!data->shouldClose) {
        data->queuemutex.lock();
        if (data->has_events()) {
            msg_request_t event = data->event_queue.front();
            data->event_queue.pop();
            data->queuemutex.unlock();
            SocketUtils sockutils;
            sockutils.writeSocket(data->getClientSocket(), event);
        }
    }
    return 1;
}

void ClientConnection::start() {
    this->reader = std::thread(connectionReader, this);
    this->writer = std::thread(connectionWriter, this);
}
void ClientConnection::stop() {
    shouldClose = true;
    this->reader.join();
    this->writer.join(); /* Guarda que tiene un while true, no es join */
    //this->server->removeClient(this); --> pedir a santi
}

void ClientConnection::push_event(struct msg_request_t event) {
    event_queue.push(event);
}

void ClientConnection::handle_message(struct msg_request_t message) {
    string content;
    content.assign(message.message.msg);
    cout << "El mensaje entrante es: " << content << endl;
}
