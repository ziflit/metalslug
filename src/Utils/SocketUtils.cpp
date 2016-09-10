#include "SocketUtils.h"
#include <iostream>
#include <errno.h>
#include <string.h>

using namespace std;

int SocketUtils::writeSocket(int fd, struct msg_request_t msg) {
    int bytesSent = send(fd, &msg, MSGSIZE, 0);
    if (bytesSent < 0) {
        cout << "Hubo un error y fue: " << strerror(bytesSent) << endl;
    }
    return bytesSent;
}

bool SocketUtils::readSocket(int socket, char* buffer) {
    int bytesRecv = 0;

    while (bytesRecv < MSGSIZE && bytesRecv != -1) {
        bytesRecv += recv(socket, buffer, MSGSIZE, 0);
    }
    if (bytesRecv == -1) {
        /* Loggeo un error */
        int interror = errno;
        cout << "Hubo un error en la lectura del socket: " << strerror(interror) << endl;
        return false;
    }

    return bytesRecv == MSGSIZE;
}
