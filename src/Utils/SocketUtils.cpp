#include "SocketUtils.h"
#include <iostream>
#include <errno.h>
#include <string.h>

using namespace std;

int SocketUtils::writeSocket(int fd, struct msg_request_t msg) {
    unsigned int realsize = sizeof(msg);

    int retcode = send(fd, (void*)&realsize, sizeof(unsigned int), 0);

    cout << realsize << endl;
    cout << retcode << endl;
    if (retcode >= 0) {
        cout << send(fd, (char*)&msg, realsize, 0) << endl;
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
    cout << "Por hacer el primer recv" << endl;
    recv(socket, (void*)&realsize, sizeof(unsigned int), 0);

    cout << "Estoy por entrar en el while, no estalló todavía: " << realsize << endl;
    while (bytesRecv < (int)realsize && bytesRecv != -1) {
        if (((int)realsize - bytesRecv) < BUFSIZE) {
            bytesRecv += recv(socket, buffer, ((int)realsize - bytesRecv), 0);
            cout << "Acabo de recibir" << bytesRecv << "bytes" << endl;
            cout << "puto" << strerror(errno) << endl;
        } else {
            bytesRecv += recv(socket, buffer, BUFSIZE, 0);
            cout << "Entró en el else" << endl;
        }
        /** std::stringstream toLog;
            toLog << "Recibidos " << bytesRecv << " bytes \n";
            LOGGER_WRITE(Logger::DEBUG, toLog.str(), CLASSNAME);**/
    }
    /**
       LOGGER_WRITE(Logger::DEBUG, "Se recibio el mensaje: " + buffer, CLASSNAME);
    */
    cout << realsize << "vs" << bytesRecv << endl;
    return bytesRecv == (int)realsize;
}
