#include "SocketUtils.h"

int SocketUtils::writeSocket(int fd, struct msg_request_t msg) {
    unsigned int realsize = sizeof(msg);

    int retcode = send(fd, (void*)&realsize, sizeof(realsize), 0);

    if (retcode >= 0) {
        send(fd, (char*)&msg, realsize, 0);
    } else {
        int interror = errno;
        return interror;
    }
    return 0;
}

bool SocketUtils::readSocket(int socket, char *buffer) {
    int bytesRecv = 0;

    /* Leo primero el tamanio de el struct a leer. El tamanio REAL */
    unsigned int realsize;
    recv(socket, &realsize, sizeof(unsigned int), 0);

    while (bytesRecv < int(realsize) && bytesRecv != -1) {
        if ((int(realsize) - bytesRecv) < BUFSIZE) {
            bytesRecv += recv(socket, buffer, (int(realsize) - bytesRecv), 0);
        } else {
            bytesRecv += recv(socket, buffer, BUFSIZE, 0);
        }
        /** std::stringstream toLog;
            toLog << "Recibidos " << bytesRecv << " bytes \n";
            LOGGER_WRITE(Logger::DEBUG, toLog.str(), CLASSNAME);**/
    }
    /**
       LOGGER_WRITE(Logger::DEBUG, "Se recibio el mensaje: " + buffer, CLASSNAME);
    */
    return bytesRecv == int(realsize);
}
