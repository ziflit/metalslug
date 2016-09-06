
#include <asm/socket.h>
#include <sys/socket.h>
#include <sstream>
#include "ClientConnection.h"
#include "../Utils/Logger.h"

#define CLASSNAME "ClientConnection.class"


int readSocket(int socket, char *buffer, int length);

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
    int result = 1;
    ClientConnection *client = (ClientConnection *) data;
    struct msg_request_t message;
    int length = sizeof(struct msg_request_t);
    char buffer[length];
    do {
        result = readSocket(client->getClientSocket(), buffer, length);

        if (result <= 0) {
            //LOGGER_WRITE(Logger::ERROR, "Error de recepcion de mensaje. \n " + strerror(errno), CLASSNAME);
            client->stop();
            //LOGGER_WRITE(Logger::ERROR, "Conexion cerrada.", CLASSNAME);
        } else {
            message = *(struct msg_request_t *) buffer;
            //HAY QUE DEFINIR QUE VAMOS A HACER CON EL MENSAJE QUE LLEGA...
            //MI IDEA ES QUE TENGAMOS UNA COLA DE EVENTOS EN EL SERVER Y QUE EL PROCESE LOS PEDIDOS
            //EN FUNCION DE LO QUE SE LE PASA
        }
    } while (result > 0);
    return 1;
}

int connectionWriter(void *data) {
    ClientConnection *client = (ClientConnection *) data;
    return 1;
}


void ClientConnection::start() {
    this->reader = std::thread(connectionReader, this);
    this->reader = std::thread(connectionWriter, this);
}

void ClientConnection::stop() {
    this->reader.detach();
    this->writer.detach();
    //this->server->removeClient(this); --> pedir a santi
}

int readSocket(int socket, char *buffer, int length) {
    int bytesRecv = 0;
    while (bytesRecv < length && bytesRecv != -1) {
        bytesRecv += recv(socket, buffer + bytesRecv, length - bytesRecv, 0);
        /** std::stringstream toLog;
        toLog << "Recibidos " << bytesRecv << " bytes \n";
        LOGGER_WRITE(Logger::DEBUG, toLog.str(), CLASSNAME);**/
    }
    /**
     LOGGER_WRITE(Logger::DEBUG, "Se recibio el mensaje: " + buffer, CLASSNAME);
     */
    return bytesRecv;
}