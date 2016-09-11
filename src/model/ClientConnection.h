
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <unistd.h>
#include "../Utils/Protocol.h"
#include "server.h"


using namespace std;

class ClientConnection {
private:
    int clientSocket;
    char username[20];
    thread reader;
    thread writer;
    Server* server;

public:
    ClientConnection();

    bool shouldClose;

    std::mutex queuemutex;

    queue<struct msg_request_t> event_queue;

    ClientConnection(int clientSocket, Server* server, char* username);

    virtual ~ClientConnection();

    int getClientSocket() { return clientSocket; }

    void handle_message(struct msg_request_t message);

    void start();

    void stop();

    void push_event(struct msg_request_t event);

    bool has_events() { return !event_queue.empty(); }

    char* getUsername();

};


#endif //METALSLUG_CLIENTCONNECTION_H
