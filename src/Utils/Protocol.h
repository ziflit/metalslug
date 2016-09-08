
#ifndef METALSLUG_PROTOCOL_H
#define METALSLUG_PROTOCOL_H

#include <string>

using namespace std;


/**
 * PROTOCOLO DE COMUNICACION ENTRE SERVER Y CLIENTES
 */


/**
 * EN VARIOS PUSE STRING PERO NO SE SI VA A FUNCAR
 * SI NO FUNCA CON STRING LO PASAMOS A CHAR[]
 */

enum MessageCode {
    CLIENT_SEND_MSG,
    CLIENT_RECIEVE_MSG
};


struct msg_t {
    string from;
    string to;
    string msg;
};


struct msg_request_t {
    MessageCode code;
    msg_t message;
};


struct msg_login {
    string username;
    string password;
};


#endif //METALSLUG_PROTOCOL_H
