#include <iostream>
#include "message.h"

string Message::getTimestamp() { return timestamp;}
string Message::getFrom(){ return from;}
string Message::getTo(){ return to;}
string Message::getContent(){ return content; }
string Message::serialize() {
    return (timestamp +","+ from +","+ to +","+ content);
}
