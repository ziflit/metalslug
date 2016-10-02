
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <unistd.h>

#include "client.h"
#include "../utils/Protocol.h"
#include "../utils/MessageUtils.h"


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

    queue<struct msg_request_t> event_queue;

    ClientHandler(int serverSocket, Client* client, const char* username);

    virtual ~ClientHandler();

    int getClientSocket() { return clientSocket; }

    void handle_message(vector<struct msg_request_t> mensajes, MessageCode code);

    void start();

    void stop();

    void push_event(struct msg_request_t event);

    bool has_events() { return !event_queue.empty(); }

    char* getUsername();

};


#endif //METALSLUG_CLIENTCONNECTION_H
