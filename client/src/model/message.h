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

class Event {
private:
    string from;
    string to;
    string content;

public:
    Event();

    //Constructor de Mensaje a un unico cliente.
    Event(string from, string to, string content);

    //Constructor de Mensaje to everyone.
    Event(string from, string content);

    //Constructor de Mensaje desde el string completo separado por comas.
    Event(string messageToDeserialize);

    string getFrom();

    string getTo();

    string getContent();

    bool isToUser(string username);

    bool isToUser(User *user);

    bool isToEveryone();

    void setFrom(const string &from);

    void setTo(const string &to);

    void setContent(const string &content);
};


class MessagesList {
private:
    std::vector<Event *> messagesList;

public:
    MessagesList();

    unsigned long size();

    void addMessage(Event *msg);

    std::vector<Event *> filterMessagesPerUser(User *user);
};


#endif //METALSLUG_MESSAGE_H
