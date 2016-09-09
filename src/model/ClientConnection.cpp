
#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "ClientConnection.h"
#include "../Utils/Logger.h"
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

ClientConnection::ClientConnection(int clientSocket, Server *server, unsigned int id, string username) {
    this->clientSocket = clientSocket;
    this->server = server;
    this->clientId = id;
    this->username = username;
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

int connectionReader(void *data) {
    bool isComplete;
    SocketUtils sockutils;
    ClientConnection *client = (ClientConnection *) data;
    struct msg_request_t message;
    char buffer[BUFSIZE];
    do {
        isComplete = sockutils.readSocket(client->getClientSocket(), buffer);

        if (!isComplete) {
            //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
            client->stop();
            //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
        } else {
            message = *(struct msg_request_t *) buffer;
            //HAY QUE DEFINIR QUE VAMOS A HACER CON EL MENSAJE QUE LLEGA...
            //MI IDEA ES QUE TENGAMOS UNA COLA DE EVENTOS EN EL SERVER Y QUE EL PROCESE LOS PEDIDOS
            //EN FUNCION DE LO QUE SE LE PASA
        }
    } while (isComplete and !client->shouldClose);
    /* Si no está completo devuelvo 0 */
    return isComplete ? 1 : 0;
}

int connectionWriter(void *data) {
    ClientConnection *client = (ClientConnection *) data;
    while (!client->shouldClose) {
        if (client->has_events()) {

        }
    }
    return 1;
}


void ClientConnection::start() {
    this->reader = std::thread(connectionReader, this);
    this->reader = std::thread(connectionWriter, this);
}

void ClientConnection::stop() {
    this->reader.join();
    this->writer.join(); /* Guarda que tiene un while true, no es join */
    //this->server->removeClient(this); --> pedir a santi
}

void ClientConnection::push_event(struct msg_request_t event) {
    event_queue.push(event);
}

