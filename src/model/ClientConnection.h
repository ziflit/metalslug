
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include "server.h"
#include <unistd.h>
#include "../Utils/Protocol.h"

using namespace std;

class ClientConnection {
private:
    int clientSocket;
    unsigned int clientId;
    string username;
    thread reader;
    thread writer;
    Server *server;

    int readSocket(int socket, char* buffer, int length);


public:

    ClientConnection(int clientSocket, Server *server, unsigned int id, string username);

    virtual ~ClientConnection();

    int getClientSocket() { return clientSocket; }

    void start();

    void stop();


};


#endif //METALSLUG_CLIENTCONNECTION_H
