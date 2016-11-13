#ifndef METALSLUG_CLIENT_H
#define METALSLUG_CLIENT_H

#define CLASSNAME "Client.class"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "message.h"
#include "../utils/SocketUtils.h"
#include "ConfigsXML.h"

using namespace std;

class ClientHandler;

class Client {
private:
    int socket_number;
    bool connected;
    ClientHandler* handler;
    char userName[20];
    std::vector<string> usersList;
    Entity my_character;
    ConfigsXML configs;
    // Configs esta compuesto por globalConf, backgroundsConfig y spritesConfig. Cada uno de ellos dentro
    // tiene un struct o vector de structs... que se pueden ver en config.h

public:
		/* Pre: ip y puerto validos
		 * Post: cliente conectado al servidor 
		 */
		bool connect_to_server(string ip, int port, string user);

		/* Pre: cliente conectado a un servidor
		 * Post: cliente desconectado del servidor
		 */
   		void disconnect();

		/* Pre: 
		 * Post: 
		 */
    int send_message(struct event evenToSend);

		/* Pre: 
		 * Post: 
		 */
		int receive_messages();

		/* Pre: 
		 * Post: envia una cantidad: "max_envios" de mensajes al
		 *       servidor, al cual esta conectado, levantando el 
		 *       contenido de los mensajes desde un archivo de texto. 
		 */
    void lorem_ipsum(int frec, int max_envios);

    void loadConfigsFromServer(struct xmlConfig globalConf, vector<struct xmlPlayer> playersConfig,
                                   vector<struct xmlEnemy> enemiesConfig,
                                   vector<struct xmlBackground> backgroundsConfig,
                                   vector<struct xmlBullet> bulletsConfig,
                                   vector<struct xmlMiscelanea> miscelaneasConfig);

    int get_socket();

    void show_users_list();

    void store_users_list();

    int sizeofUserList();

    void ask_for_messages();

    void send_message_to_all(string content);

    string searchUser(int user);

    std::vector<string> makeUsersList(Event *msg);

    void send_disconnect_to_server();

    void handle_message(Event *message, EventCode code);

    bool is_connected() { return connected; }

    void set_connection_status(bool status) { this->connected = status; }

    ClientHandler* getHandler() {
        return handler;
    }

    Entity getEntity() {
        return my_character;
    }
	ConfigsXML getConfigs(){ return (configs);}
    ClientHandler* start_connection();
};


#endif //METALSLUG_CLIENT_H
