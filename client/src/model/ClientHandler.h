
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <unistd.h>

#include "client.h"
#include "../utils/Protocol.h"


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

    std::mutex queuemutex;

    queue<struct event> event_queue;

    ClientHandler(int serverSocket, Client* client, const char* username);

    virtual ~ClientHandler();

    int getClientSocket() { return clientSocket; }

    void handle_message(vector<struct event> mensajes, EventCode code);

    void start();

    void stop();

    void push_event(struct event event);

    bool has_events() { return !event_queue.empty(); }

    char* getUsername();

    void setSocketTimeout() const;
};


#endif //METALSLUG_CLIENTCONNECTION_H
