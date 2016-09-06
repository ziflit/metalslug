
#include <asm/socket.h>
#include <sys/socket.h>
#include "ClientConnection.h"

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
    ClientConnection *client = (ClientConnection *) data;

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
    //this->server->removeClient(this);
}