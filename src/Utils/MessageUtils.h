
#ifndef METALSLUG_MESSAGEUTILS_H
#define METALSLUG_MESSAGEUTILS_H


#include <vector>
#include "Protocol.h"
#include "../model/message.h"

class MessageUtils {
public:
    vector<struct msg_request_t> &buildRequests(Message *message);

    Message &buildMessages(Message *message);
};


#endif //METALSLUG_MESSAGEUTILS_H
