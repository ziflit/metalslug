#ifndef METALSLUG_SOCKUTIL_H
#define METALSLUG_SOCKUTIL_H

#include "Protocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

class SocketUtils {
    private:
    public:
    int writeSocket(int fd, struct event msg);
    int writeSocket(int fd, void* msg, size_t size);
    bool peek(int fd, char* buffer);
    bool readSocket(int socket, char *buffer);
};
#endif
