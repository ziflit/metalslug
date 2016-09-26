#ifndef METALSLUG_CLIENT_H
#define METALSLUG_CLIENT_H
#define CLASSNAME "Client.class"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "message.h"
#include "../Utils/SocketUtils.h"
#include "../Utils/MessageUtils.h"

using namespace std;

class ClientHandler;

class Client {
private:
    int socket_number;
    ClientHandler* handler;
    char userName[20];
    std::vector<string> usersList;
public:
		/* Pre: ip y puerto validos
		 * Post: cliente conectado al servidor 
		 */
		bool connect_to_server(string ip, int port);

		/* Pre: cliente conectado a un servidor
		 * Post: cliente desconectado del servidor
		 */
   		void disconnect();

		/* Pre: 
		 * Post: 
		 */
    int send_message(int to, string content);

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

    int get_socket();

    void show_users_list();

    void store_users_list();

    int sizeofUserList();

    void ask_for_messages();

    void send_message_to_all(string content);

    string searchUser(int user);

    std::vector<string> makeUsersList(Message *msg);

    void send_disconnect_to_server();

    void handle_message(Message *message, MessageCode code);
};


#endif //METALSLUG_CLIENT_H
