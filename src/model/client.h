#ifndef METALSLUG_CLIENT_H
#define METALSLUG_CLIENT_H
#define BUFSIZE 1024
#define CLASSNAME "Client.class"
#include <iostream>
#include <stdlib.h>
#include "message.h"
#include "../Utils/SocketUtils.h"
#include "../Utils/MessageUtils.h"



class Client {
	private:
    int socket_number;
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
};


#endif //METALSLUG_CLIENT_H
