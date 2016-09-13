
#ifndef METALSLUG_PROTOCOL_H
#define METALSLUG_PROTOCOL_H

#include <string>

#define BUFSIZE 256
#define CONTENT_TRANSFER_SIZE 200
#define MSGSIZE sizeof(struct msg_request_t)

using namespace std;


/**
 * PROTOCOLO DE COMUNICACION ENTRE SERVER Y CLIENTES
 */


/**
 * EN VARIOS PUSE STRING PERO NO SE SI VA A FUNCAR
 * SI NO FUNCA CON STRING LO PASAMOS A CHAR[]
 */

enum MessageCode {
    CLIENT_SEND_MSG, /* El cliente quiere enviar un mensjae*/
    CLIENT_RECEIVE_MSGS, /* El cliente quiere recibir sus mensajes*/
    LOGIN_OK, /* El servidor auntentico bien al cliente */
    LOGIN_FAIL, /* El servidor no autentico bien al cliente */
    USERS_LIST_MSG, /* El servidor envia al cliente los usuarios */
    LAST_MESSAGE /* Es el ultimo mensaje, para saber hasta cuando recibir */
};

enum MessageCompletion {
    FINAL_MSG,
    PARTIAL_MSG,
};

struct msg_t {
    char from[20];
    char to[20];
    char msg[200];
};

struct msg_request_t {
    MessageCode code;
    MessageCompletion completion;
    msg_t message;
};


struct msg_login {
    string username;
    string password;
};


#endif //METALSLUG_PROTOCOL_H
