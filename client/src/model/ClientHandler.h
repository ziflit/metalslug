
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <mutex>
#include <thread>
#include <vector>
#include <list>
#include <string.h>
#include <asm/socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "client.h"
#include "../utils/Logger.h"
#include "../utils/Protocol.h"
#include "../utils/SocketUtils.h"

class Client;


using namespace std;

class ClientHandler {
private:
    int clientSocket;
    char username[20];

    thread reader;
    thread writer;
    thread control;

    Client* client;
public:
    ClientHandler();

    bool shouldClose;

    std::mutex incommingMutex;
    std::mutex outgoingMutex;

    list<struct event> incommingEvents;
    list<struct event> outgoingEvents;

    ClientHandler(int serverSocket, Client* client, const char* username);

    virtual ~ClientHandler();

    int getClientSocket() { return clientSocket; }

    void handle_message(vector<struct event> mensajes, EventCode code);

    void start();

    void stop();

    void sendEvent(struct event event);

    inline bool has_events() { return !incommingEvents.empty(); }

    char* getUsername();

    void setSocketTimeout() const;

    vector<struct event> getModelState();
};


#endif //METALSLUG_CLIENTCONNECTION_H
