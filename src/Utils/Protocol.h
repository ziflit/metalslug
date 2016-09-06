
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
    CLIENT_RECIEVE_MSG,
};

struct msg_send_request_t {
    MessageCode code;
    msg_send_t message;
};

struct msg_send_t {
    string from;
    string to;
    string msg;
};

struct msg_receive_request_t {
    MessageCode code;
    msg_receive_t message;
};

struct msg_receive_t {
    string username;
};

struct msg_login {
    string username;
    string password;
};


#endif //METALSLUG_PROTOCOL_H
