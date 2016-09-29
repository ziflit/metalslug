#include "message.h"

#include <iostream>


//_______________________________Messages______________________________________


Message::Message() {}

Message::Message(string from, string to, string content) {
    this->from = from;
    this->to = to;
    this->content = content;
}

Message::Message(string from, string content) {
    this->from = from;
    this->to = "everyone";
    this->content = content;
}

Message::Message(string messageToDeserialize) {

    std::string msg = messageToDeserialize;
    std::string delimiter = ",";

    size_t pos = 0;
    std::string token;

    pos = msg.find(delimiter);
    msg.erase(0, pos + delimiter.length());

    pos = msg.find(delimiter);
    this->from = msg.substr(0, pos);
    msg.erase(0, pos + delimiter.length());

    pos = msg.find(delimiter);
    this->to = msg.substr(0, pos);
    msg.erase(0, pos + delimiter.length());

    pos = msg.find(delimiter);
    this->content = msg.substr(0, pos);
    msg.erase(0, pos + delimiter.length());
}

string Message::getFrom() { return from; }

string Message::getTo() { return to; }

string Message::getContent() { return content; }

bool Message::isToUser(string username) { return (to == username || to == "everyone"); }

bool Message::isToUser(User *user) {
    return (user->isMyUsername(to.data()));
}

bool Message::isToEveryone() { return (to == "everyone"); }

void Message::setFrom(const string &from) {
    Message::from = from;
}

void Message::setTo(const string &to) {
    Message::to = to;
}

void Message::setContent(const string &content) {
    Message::content = content;
}

//_______________________________MessagesList__________________________________

MessagesList::MessagesList() {}

unsigned long MessagesList::size() {
    return messagesList.size();
}


void MessagesList::addMessage(Message *msg) {
    messagesList.push_back(msg);
}

std::vector<Message *> MessagesList::filterMessagesPerUser(User *user) {
    std::vector<Message *> messagesFiltered;

    vector<Message *>::iterator it = messagesList.begin();

    while (it != messagesList.end()) {

        if ((*it)->isToUser(user)) {
            messagesFiltered.push_back((*it));

            if ((*it)->isToEveryone()) {
                ++it;
                //no borra el mensaje por ser to everyone.
            } else if (!(*it)->isToEveryone()) {
                messagesList.erase(it++);
                //elima el mensaje de messagesList
            }
        } else ++it;
    }


    return messagesFiltered;
}
