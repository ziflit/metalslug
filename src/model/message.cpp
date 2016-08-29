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
