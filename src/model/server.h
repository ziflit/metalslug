#ifndef METALSLUG_SERVER_H
#define METALSLUG_SERVER_H


class Server {
	private:
	    int log_type; /* Para saber que tipo de log se va usar */
		ListaDeMensajes lista_de_mensajes /* Lista de mensajes almacenados */

	public:

		/* Pre: servidor creado
		 * Post: servidor on-line esperando conexiones
		 */
		int initialize_server();

		/* Pre: servidor creado
		 * Post: servidor on-line esperando conexiones
		 */
		int start_listening();

		/* Pre: 
		 * Post: envia los mensajes, que tiene almacenados,
		 *       para el usuario solicitado.
		 */
		int retrieve_messages(User user);

		/* Pre: 
		 * Post: cierra la conexion de un cliente especifico
		 */
		int close_connection();

		/* Pre: 
		 * Post: cierra todas las conexiones
		 */
		int close_all_connections();

};


#endif //METALSLUG_SERVER_H