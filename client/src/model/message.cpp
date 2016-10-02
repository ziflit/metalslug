#include "message.h"

#include <iostream>


//_______________________________Messages______________________________________


Event::Event() {}

Event::Event(string from, string to, string content) {
    this->from = from;
    this->to = to;
    this->content = content;
}

Event::Event(string from, string content) {
    this->from = from;
    this->to = "everyone";
    this->content = content;
}

Event::Event(string messageToDeserialize) {

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

string Event::getFrom() { return from; }

string Event::getTo() { return to; }

string Event::getContent() { return content; }

bool Event::isToUser(string username) { return (to == username || to == "everyone"); }

bool Event::isToUser(User *user) {
    return (user->isMyUsername(to.data()));
}

bool Event::isToEveryone() { return (to == "everyone"); }

void Event::setFrom(const string &from) {
    Event::from = from;
}

void Event::setTo(const string &to) {
    Event::to = to;
}

void Event::setContent(const string &content) {
    Event::content = content;
}

//_______________________________MessagesList__________________________________

MessagesList::MessagesList() {}

unsigned long MessagesList::size() {
    return messagesList.size();
}


void MessagesList::addMessage(Event *msg) {
    messagesList.push_back(msg);
}

std::vector<Event *> MessagesList::filterMessagesPerUser(User *user) {
    std::vector<Event *> messagesFiltered;

    vector<Event *>::iterator it = messagesList.begin();

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
