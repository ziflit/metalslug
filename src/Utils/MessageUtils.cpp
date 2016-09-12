

#include "MessageUtils.h"

vector<struct msg_request_t> &buildRequests(Message *message) {
    vector<struct msg_request_t> result;
    int offset = 0;
    while (offset <= message->getContent().length()) {
        int remaining = message->getContent().length() - offset;
        struct msg_t msg;
        strcpy(msg.from, message->getFrom().c_str());
        strcpy(msg.to, message->getTo().c_str());
        if (remaining <= CONTENT_TRANSFER_SIZE) {
            string fragment = message->getContent().substr(offset, offset + remaining);
            strcpy(msg.msg, fragment.c_str());
            offset += message->getContent().length();
        } else {
            string fragment = message->getContent().substr(offset, offset + CONTENT_TRANSFER_SIZE);
            strcpy(msg.msg, fragment.c_str());
            offset += CONTENT_TRANSFER_SIZE;
        }
        struct msg_request_t request;
        request.message = msg;
        result.push_back(request);
    };
    return result;
}

Message &buildMessage(vector<struct msg_request_t> requests) {
    Message message;
    struct msg_request_t first = requests.front();
    message.setTo(first.message.to);
    message.setFrom(first.message.from);
    for (struct msg_request_t req : requests) {
        string content = message.getContent();
        message.setContent(content + req.message.msg);
    }
    return message;
}