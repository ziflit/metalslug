#include <asm/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include "ClientHandler.h"
#include "../Utils/Logger.h"

#define CLASSNAME "ClientHandler.class"


ClientHandler::~ClientHandler() {
    close(this->clientSocket);
}

/**
 * @param clientSocket <--- socket id
 * @param client
 * @param username
 */
ClientHandler::ClientHandler(int clientSocket, Client *client, const char *username) {
    this->clientSocket = clientSocket;
    this->client = client;
    strcpy(this->username, username);
    this->shouldClose = false;


    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }

    timeout.tv_sec = 10;
    if (setsockopt(this->clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout))) {
        cout << "Error on setting timeout" << endl;
    }
}

void sendHeartbeat(ClientHandler* handler) {
    struct msg_request_t alive;
    alive.code = MessageCode::MSG_OK;
    while (!handler->shouldClose) { // while está vivo
        handler->push_event(alive);
        sleep(5);
    }
}

void receiveHeartbeat(ClientHandler *handler) {
    bool is_server_alive;
    SocketUtils sockutils;
    vector<struct msg_request_t> mensajes;
    char buffer[BUFSIZE];

    while (!handler->shouldClose) {
        is_server_alive = sockutils.peek(handler->getClientSocket(), buffer);
        if (not is_server_alive and !handler->shouldClose) {
            handler->stop();
            break;
        }
    }
}

int connectionWriter(ClientHandler *data) {
    int result;
    while (!data->shouldClose) {
        data->queuemutex.lock();
        if (data->has_events()) {
            msg_request_t event = data->event_queue.front();
            data->event_queue.pop();
            data->queuemutex.unlock();
            SocketUtils sockutils;
            result = sockutils.writeSocket(data->getClientSocket(), event);
            if (result == -1) {
                cout << "El servidor está desconectado" << endl;
                if (!data->shouldClose) {
                    data->stop();
                }
            }

        } else { data->queuemutex.unlock(); }
    }
    return 1;
}

void ClientHandler::start() {
    this->reader = std::thread(receiveHeartbeat, this);
    this->writer = std::thread(connectionWriter, this);
    this->control = std::thread(sendHeartbeat, this);
}

void ClientHandler::stop() {
    if (not shouldClose) {
        this->shouldClose = true;
        close(this->clientSocket);
        this->writer.detach(); /* Guarda que tiene un while true, no es join */
        this->reader.detach();
        this->control.detach();
        this->client->set_connection_status(false);
    }
}

void ClientHandler::push_event(struct msg_request_t event) {
    this->queuemutex.lock();
    event_queue.push(event);
    this->queuemutex.unlock();
}

void ClientHandler::handle_message(vector<struct msg_request_t> mensajes, MessageCode code) {
    MessageUtils messageutils;
    Message* message = messageutils.buildMessage(mensajes);
    this->client->handle_message(message, code);
}

ClientHandler::ClientHandler() {}

char *ClientHandler::getUsername() {
    return username;
}
