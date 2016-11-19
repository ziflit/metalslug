
#ifndef METALSLUG_PROTOCOL_H
#define METALSLUG_PROTOCOL_H

#include <string>
#include <vector>

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
	SDL_KEY_A_PRESSED,
	SDL_KEY_S_PRESSED,
	SDL_KEYUP_RELEASED,
	SDL_KEYDOWN_RELEASED,
	SDL_KEYLEFT_RELEASED,
	SDL_KEYRIGHT_RELEASED,
	SDL_KEY_A_RELEASED,
	SDL_KEY_S_RELEASED,
	PLAYER_STATUS,
	BACKGROUND_STATUS,
	ENEMY_STATUS,
	BULLET_STATUS,
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
	ENEMY_NORMAL_1,
	ENEMY_NORMAL_2,
	ENEMY_NORMAL_3,
	ENEMY_FINAL_1,
	ENEMY_FINAL_2,
	ENEMY_FINAL_3,
	BACKGROUND_LVL1_Z0,   
	BACKGROUND_LVL1_Z1,
    BACKGROUND_LVL1_Z2,
    BACKGROUND_LVL2_Z0,   
	BACKGROUND_LVL2_Z1,
    BACKGROUND_LVL2_Z2,
	BACKGROUND_LVL3_Z0,   
	BACKGROUND_LVL3_Z1,
    BACKGROUND_LVL3_Z2,
	NOPLAYER,
	BT_BULLET,			// BT = Bullet Type
	BT_HEAVY_BULLET,
	BT_MISSILE,
	BT_TELE_MISSILE,
	BT_SHOT,
	BT_BOMB,
	BT_LASER,
	MSC_WEAPON_BOX_HEAVY,    // MSC = Miscelanea
	MSC_WEAPON_BOX_ROCKET,
	MSC_WEAPON_BOX_SHOT,
	MSC_WEAPON_BOX_CHASER,
	MSC_POWER_BONUS,
	MSC_BONUS_KILLALL,
	MSC_PLATFORM
};

enum Postura{
	CAMINANDO_IZQUIERDA,
	MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA,
	AGACHADO_MIRANDO_IZQUIERDA_QUIETO,
	MIRANDO_ARRIBA_IZQUIERDA_QUIETO,
	CAMINANDO_DERECHA,
	MIRANDO_ARRIBA_CAMINANDO_DERECHA,
	AGACHADO_MIRANDO_DERECHA_QUIETO,
	MIRANDO_ARRIBA_DERECHA_QUIETO,
	AGACHADO_AVANZANDO_IZQUIERDA,
	AGACHADO_AVANZANDO_DERECHA,
	MIRANDO_DERECHA_QUIETO,
    MIRANDO_IZQUIERDA_QUIETO,
    DESCONECTADO,
	DISPARANDO_DERECHA_QUIETO,
	DISPARANDO_IZQUIERDA_QUIETO,
	DISPARANDO_CAMINANDO_DERECHA,
	DISPARANDO_CAMINANDO_IZQUIERDA,
	DISPARANDO_AGACHADO_QUIETO_DERECHA,
	DISPARANDO_AGACHADO_QUIETO_IZQUIERDA,
	DISPARANDO_MIRANDO_ARRIBA_DERECHA_QUIETO,
	DISPARANDO_MIRANDO_ARRIBA_IZQUIERDA_QUIETO,
	DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_DERECHA,
	DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_IZQUIERDA,
	MURIENDO,
	MUERTO

};

enum Arma{
	PISTOLA,
	HEAVY_MACHINEGUN,
	ROCKET_LAUNCHER,
	ENEMY_CHASER,
	SHOTGUN,
	BOMB
};

struct event_ext {
	EventCode code;
	Entity id;
	char username[20];
	int x;
	int y;
	int puntaje;
	Postura postura;
    Arma arma;
};

struct event {
	EventCompletion completion;
	event_ext data;
};

// Structs para el envio de la configuracion inicial, en base al XML

struct xmlConfig {
	int ancho;
	int alto;
	int cant_players;
};

struct xmlPlatform { 
	int x;
	int y;
	int ancho;
	int alto;
};

struct xmlLvl {
    EventCompletion completion;
	int id; 
	int cant_enemies;
	int cant_boxes;
	int posXtoFinish;
	vector<struct xmlPlatform> platforms;
};

struct xmlPlayer {
    EventCompletion completion;
	Entity id;
	char pathColor[40];
	char pathGrey[40];
	char pathWeapons[40];
	int ancho;
	int alto;
	int cantWidthFrames;
	int cantHeightFrames;
	int speed;
};

struct xmlEnemy {
	EventCompletion completion;
	Entity id;
	char path[40];
	int ancho;
	int alto;
    int cantWidthFrames;
    int cantHeightFrames;
	int speed;
};

struct xmlBackground {
    EventCompletion completion;
	Entity id;
	char path[40];
	int ancho;
	int alto;
};

struct xmlBullet {
    EventCompletion completion;
    Entity id;
    char path[40];
    int ancho;
    int alto;
};

struct xmlMiscelanea {
    EventCompletion completion;
    Entity id;
    char path[40];
    int ancho;
    int alto;
};
//---------------------------------------------------

#endif //METALSLUG_PROTOCOL_H
