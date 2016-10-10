
#ifndef METALSLUG_PROTOCOL_H
#define METALSLUG_PROTOCOL_H

#include <string>

#define BUFSIZE 256
#define CONTENT_TRANSFER_SIZE 200
#define MSGSIZE sizeof(struct event)

using namespace std;


/**
 * PROTOCOLO DE COMUNICACION ENTRE SERVER Y CLIENTES
 */


/**
 * EN VARIOS PUSE STRING PERO NO SE SI VA A FUNCAR
 * SI NO FUNCA CON STRING LO PASAMOS A CHAR[]
 */

enum EventCode {
    CLIENT_SEND_MSG, /* El cliente quiere enviar un mensjae*/
    CLIENT_RECEIVE_MSGS, /* El cliente quiere recibir sus mensajes*/
    LOGIN_OK, /* El servidor auntentico bien al cliente */
    LOGIN_FAIL, /* El servidor no autentico bien al cliente */
    USERS_LIST_MSG, /* El servidor envia al cliente los usuarios */
    LAST_MESSAGE, /* Es el ultimo mensaje, para saber hasta cuando recibir */
    CLIENT_DISCONNECT, /* El cliente se desconecta del servidor */
    MSG_OK, /* ACK */
    SDL_KEYUP_PRESSED,
    SDL_KEYDOWN_PRESSED,
    SDL_KEYLEFT_PRESSED,
    SDL_KEYRIGHT_PRESSED,
    SDL_KEYUP_RELEASED,
    SDL_KEYDOWN_RELEASED,
    SDL_KEYLEFT_RELEASED,
    SDL_KEYRIGHT_RELEASED,
	PLAYER_STATUS,
    BACKGROUND_STATUS,
    TODO_SIGUE_IGUAL
};

enum EventCompletion {
    FINAL_MSG,
    PARTIAL_MSG,
};

enum Entity {
    MARCO,
    TARMA,
    FIO,
    ERI,
    ENEMY_NORMAL,
    LEVEL1_Z1,    // fondo del level 1, con Z-index 1
    LEVEL1_Z2,
    LEVEL1_Z3,
    LEVEL2_Z1,
    LEVEL2_Z2,
    LEVEL2_Z3,    
};

struct event_ext {
    EventCode code;
    Entity id;
    unsigned int x;
    unsigned int y;
    unsigned int h;
};

struct event {
    EventCompletion completion;
    event_ext data;
};


struct msg_login {
    string username;
    string password;
};


#endif //METALSLUG_PROTOCOL_H
