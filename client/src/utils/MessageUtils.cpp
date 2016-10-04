

#include "MessageUtils.h"

vector<struct msg_request_t>& MessageUtils::buildRequests(Event *message, EventCode code) {
    vector<struct msg_request_t>* result = new vector<struct msg_request_t>();
    int offset = 0;
    while (offset <= message->getContent().length() - 1) {
        int remaining = message->getContent().length() - offset;
        struct msg_t msg;
        EventCompletion completion;
        strcpy(msg.from, message->getFrom().c_str());
        strcpy(msg.to, message->getTo().c_str());
        if (remaining <= CONTENT_TRANSFER_SIZE) {
            string fragment = message->getContent().substr(offset, offset + remaining);
            strcpy(msg.msg, fragment.c_str());
            offset += message->getContent().length();
            completion = EventCompletion::FINAL_MSG;
        } else {
            string fragment = message->getContent().substr(offset, offset + CONTENT_TRANSFER_SIZE);
            strcpy(msg.msg, fragment.c_str());
            offset += CONTENT_TRANSFER_SIZE;
            completion = EventCompletion::PARTIAL_MSG;
        }
        struct msg_request_t request;
        request.message = msg;
        request.completion = completion;
        request.code = code;
        result->push_back(request);
    };
    cout << "este es el tamanio del vector" << result->size() << endl;
    return *result;
}

Event* MessageUtils::buildMessage(vector<struct msg_request_t> requests) {
    Event* message = new Event();
    struct msg_request_t first = requests.front();
    message->setTo(first.message.to);
    message->setFrom(first.message.from);
    for (struct msg_request_t req : requests) {
        string content = message->getContent();
        message->setContent(content + req.message.msg);
    }
    return message;
}
