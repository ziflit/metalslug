#ifndef METALSLUG_SOCKUTIL_H
#define METALSLUG_SOCKUTIL_H

#include "Protocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

class SocketUtils {
    private:
    public:
    int writeSocket(int fd, struct msg_request_t msg);
    int peek(int fd, char* buffer);
    bool readSocket(int socket, char *buffer);
};
#endif
