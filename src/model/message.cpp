#include <iostream>
#include <iostream>
#include "message.h"


int Message::getTimestamp() { return timestamp;}

string Message::getFrom(){ return from;}

string Message::getTo(){ return to;}

string Message::getContent(){ return content; }

string Message::serialize() {
    return (to_string(timestamp) +","+ from +","+ to +","+ content);
}
bool Message::isToUser(string username) {
    if(to == username || to == "everyone")return true;
    return false;
}
Message::Message(unsigned long timestamp, string from, string content) {
    this->timestamp = timestamp;
    this->from = from;
    this->to = "everyone";
    this->content = content;

}
Message::Message(unsigned long timestamp, string from, string to, string content) {
    this->timestamp = timestamp;
    this->from = from;
    this->to=to;
    this->content = content;
}

MessagesList::MessagesList() {
    lista_mensajes = new std::vector<Message>();
}

std::vector<Message> MessagesList::filter_messages_per_user(User user){
    std::vector<Message> messages = new std::vector<Message>();




    return messages;
}