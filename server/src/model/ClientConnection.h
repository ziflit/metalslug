
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <unistd.h>

#include "server.h"
#include "../utils/Protocol.h"
#include "../utils/MessageUtils.h"


using namespace std;

class ClientConnection {
private:
    int clientSocket;
    char username[20];
    thread reader;
    thread writer;
    thread control;
    Server* server;

public:
    ClientConnection();

    bool shouldClose;

    std::mutex queuemutex;

    list<struct event> event_queue;

    ClientConnection(int clientSocket, Server* server, char* username);

    virtual ~ClientConnection();

    int getClientSocket() { return clientSocket; }

    void handle_message(vector<struct event> mensajes, EventCode code);

    void start();

    void stop();

    void push_event(struct event event);

    bool has_events() { return !event_queue.empty(); }

    char* getUsername();

};


#endif //METALSLUG_CLIENTCONNECTION_H
