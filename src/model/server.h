#ifndef METALSLUG_SERVER_H
#define METALSLUG_SERVER_H

#include "message.h"
#include <list>
#include "../Utils/Protocol.h"

#define MAX_CONN 10
#define BUFSIZE 1024

struct arg_struct {
    int id;
    int* connections;
};

class Server {
	private:
    int log_type; /* Para saber que tipo de log se va usar */
    int listen_port;
    std::list<msg_t> messagesList; /* Lista de mensajes almacenados */
    int listen_socket_fd;
    int clients[MAX_CONN];
    pthread_t th_clientes[MAX_CONN];

  public:
    /* Dada una ip y un puerto para escuchar, pide un socket al sistema
     * y bindea el proceso a esa dirección.
     * Devuelve el file descriptor del socket ya bindeado para su uso.
     */
    int initialize_server(string ip, int port);

    /* Devuelve el fd del socke en el cual escucha el server */
    int get_listen_socket();

		/* Pre: servidor creado
		 * Post: servidor on-line esperando conexiones
		 */
    void start_listening();

    /* Pre:
		 * Post: envia los mensajes, que tiene almacenados,
		 *       para el usuario solicitado.
		 */
		int retrieve_messages(User user);

    /* Pre:
     * Post: cierra la conexion de un cliente especifico y
     * actualiza la lista de conexiones disponibles liberando un lugar
		 */
    int close_connection(int client_id);

    /* Pre:
     * Post: cierra todas las conexiones
     * Cierra todas las conexiones activas del servidor.
		 */
    void close_all_connections();

    /* Cierra el socket de listening y todos los de clientes */
    /* y sus threads */
    void shutdown();

    int* get_connections();

    /* Completa la lista de conexiones de clientes con sus respectivos
     * fd para identificarlos. También genera los threads de intercambio
     * de mensajes para cada cliente conectado.
     */
    void accept_incoming_connections();

    /* guarda el mensaje pasado en la lista de mensajes que tiene almacenada */
    void store_message();

    /* filtra la lista de mensajes almacenados, y devuelve todos los que le
     * pertencen al usuario solicitado*/
    list<msg_t> get_messages_of(string user);;



};


#endif //METALSLUG_SERVER_H
