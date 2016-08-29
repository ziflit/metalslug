#ifndef METALSLUG_CLIENT_H
#define METALSLUG_CLIENT_H

#include <iostream>
#include "message.h"

class Client {
	private:
	    MessageList my_messages;
	    int socket_number;
	public:
		/* Pre: ip y puerto validos
		 * Post: cliente conectado al servidor 
		 */
		int connect_to_server(string ip, int port);

		/* Pre: cliente conectado a un servidor
		 * Post: cliente desconectado del servidor
		 */
    void disconnect();

		/* Pre: 
		 * Post: 
		 */
		int send_message(Message* msg);

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
};


#endif //METALSLUG_CLIENT_H
