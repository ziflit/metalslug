
#ifndef METALSLUG_CLIENTCONNECTION_H
#define METALSLUG_CLIENTCONNECTION_H

#include <string>
#include <thread>
#include <queue>
#include <unistd.h>
#include "../Utils/Protocol.h"

using namespace std;

class Server;
class ClientConnection {
private:
    int clientSocket;
    unsigned int clientId;
    string username;
    thread reader;
    thread writer;
    queue<struct msg_request_t> event_queue;
    Server *server;

    int readSocket(int socket, char* buffer, int length);


public:
    bool shouldClose;

    ClientConnection(int clientSocket, Server *server, unsigned int id, string username);

    virtual ~ClientConnection();

    int getClientSocket() { return clientSocket; }

    void start();

    void stop();

    void push_event(struct msg_request_t event);

    bool has_events() { return !event_queue.empty(); }

};


#endif //METALSLUG_CLIENTCONNECTION_H
