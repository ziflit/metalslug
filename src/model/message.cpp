#include <iostream>
#include <iostream>
#include "message.h"

//_______________________________Messages______________________________________

Message::Message(int timestamp, string from, string to, string content) {
    this->timestamp = timestamp;
    this->from = from;
    this->to = to;
    this->content = content;
}

Message::Message(int timestamp, string from, string content) {
    this->timestamp = timestamp;
    this->from = from;
    this->to = "everyone";
    this->content = content;
}

int Message::getTimestamp() { return timestamp;}

string Message::getFrom(){ return from;}

string Message::getTo(){ return to;}

string Message::getContent(){ return content; }

string Message::serialize() {
    return (to_string(timestamp) +","+ from +","+ to +","+ content);
}

bool Message::isToUser(string username) { return (to == username || to == "everyone"); }

bool Message::isToEveryone() { return (to == "everyone");}

//_______________________________MessagesList__________________________________

void MessagesList::addMessage(Message msg) {
    messagesList.push_back(msg);
}

std::vector<Message> MessagesList::filterMessagesPerUser(User user){
    std::vector<Message> messagesFiltered;

    vector<Message>::iterator it = messagesList.begin();

    while(it != messagesList.end()){

        if(it->isToUser(user.getUsername())){
            Message* msg = new Message(it->getTimestamp(),it->getFrom(),it->getTo(),it->getContent());
            messagesFiltered.push_back((*msg));

            if(it->isToEveryone()){
                ++it;
                //no borra el mensaje por ser to everyone.
            }
            else if(! it->isToEveryone()){
                messagesList.erase(it++);
                //elima el mensaje de messagesList
            }
        }
        else ++it;
    }


    return messagesFiltered;
}