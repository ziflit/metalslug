#ifndef METALSLUG_MESSAGE_H
#define METALSLUG_MESSAGE_H

#define ASKUSER 1
#define ASKPASS 2
#define GETUSERMESSAGES 3
#define ENDOFMESSAGES 4


#include <iostream>
#include <string.h>
#include "User.h"

#include <vector>

class Message {
private:
    int id;
    int timestamp;
    string from;
    string to;
    string content;

public:
    Message();

    //Constructor de Mensaje a un unico cliente.
    Message(int timestamp, string from, string to, string content);

    //Constructor de Mensaje to everyone.
    Message(int timestamp, string from, string content);

    //Constructor de Mensaje desde el string completo separado por comas.
    Message(string messageToDeserialize);

    int getTimestamp();

    string getFrom();

    string getTo();

    string getContent();

    string serialize();

    bool isToUser(string username);

    bool isToUser(User *user);

    bool isToEveryone();

    void setFrom(const string &from);

    void setTo(const string &to);

    void setContent(const string &content);
};


class MessagesList {
private:
    std::vector<Message *> messagesList;

public:
    MessagesList();

    unsigned long size();

    void addMessage(Message *msg);

    std::vector<Message *> filterMessagesPerUser(User *user);
};


#endif //METALSLUG_MESSAGE_H
