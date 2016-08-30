#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "server.h"

using namespace std;

/* Función para el thread de comunicación con el cliente
 * Manda los mensajes que se ingresen por cin()
 */
void* client_comm(void* args) {
    /* Mensaje de bienvenida. Se manda una vez fijo */
    string message;
    int client_id = ((arg_struct*)args)->id;
    int* clients = ((arg_struct*)args)->connections;

    message = "Estás conectado! Bienvenido!";
    send(clients[client_id], message.data(), BUFSIZE, 0);

    /* endofcomm indica si se da por terminada la comunicación con el cliente
     * se da por terminado el intercambio si el server envía un mensaje con sólo
     * "#". Ese último mensaje no se envía, simplemente se corta toda comunicación
    */
    bool endofcomm = false;
    while (!endofcomm) {
        getline(cin, message);
        if (message == "#") {
            endofcomm = true;
            break;
        }
        send(clients[client_id], message.data(), BUFSIZE, 0);
    }
    return NULL;
}

int Server::get_listen_socket() {
    return listen_socket_fd;
}

int Server::initialize_server(string ip, int port) {
    struct sockaddr_in server_addr;
    socklen_t addr_size;
    /* Creo el primer socket
     * AF_INET indica IPv4
     * SOCK_STREAM indica tipo de socket de stream binario
     * IPPROTO_TCP indica TCP
     * socket() devuelve un file descriptor (int) que se refiere a
     * el socket asignado por el sistema operativo. El servidor todavia
     * no esta conectado al socket
    */
    listen_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket_fd < 0) {
        cout << "\nError en la creacion del socket" << endl;
        exit(1);
    }
    /* Configuro los datos del servidor
     * Para enviarlos al socket
    */
    server_addr.sin_family = AF_INET;
    /* inet_addr() transforma el string en el unsigned long que espera s_addr */
    server_addr.sin_addr.s_addr = inet_addr(ip.data());
    /* htons() devuelve el tipo de dato necesario para sin_port (unsigned int)*/
    server_addr.sin_port = htons(port);
    addr_size = sizeof(server_addr);

    /* Asigno el nombre al socket usando bind():
     * es decir, le asigno una direccion
    */
    if (bind(listen_socket_fd, (struct sockaddr*)&server_addr, addr_size) < 0) {
        cout << "Hubo un error al hacer el binding del socket: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }
    return listen_socket_fd;
}

void Server::start_listening() {
    listen(listen_socket_fd, MAX_CONN);
}

void Server::shutdown() {
    for (int i=0; i < MAX_CONN; ++i) {
        pthread_join(th_clientes[i], NULL);
    }
    close_all_connections();
    close(listen_socket_fd);
}

void Server::accept_incoming_connections() {
    int client_id = 0;
    struct sockaddr_in client_addr;
    socklen_t caddr_size;

    while (client_id < MAX_CONN) {
        /* accept() devuelve un file descriptor asociado a la conexión con el cliente
         * y sólo a el */
        clients[client_id] = accept(listen_socket_fd, (struct sockaddr*)&client_addr,
                                    &caddr_size);
        if (clients[client_id] < 0) {
            cout << "Hubo un error al conectar con el cliente: " << strerror(errno) << endl;
            cout << "Cerrando..." << endl;
            exit(1);
        }

        struct arg_struct args;
        args.connections = get_connections();
        args.id = client_id;
        pthread_create(&th_clientes[client_id], NULL, client_comm, &args);
        client_id++;
    }
}

void Server::close_all_connections() {
    for (int i=0; i<MAX_CONN; ++i) {
        close(clients[i]);
    }
}

int* Server::get_connections() {
    return clients;
}

int main(int argc, char* argv[]) {
    /* Variables iniciales
     * int port: puerto en el cual el server escucha
     * int lserver_socket_fd: file desc. para el socket de listen
     * char buffer[BUFSIZE]: buffer para transferencia de mensajes
     * struct sockaddr_in client_addr: se guardan aca los datos del cliente conectado
    */
    int port = 0;
    string ip = "127.0.0.1";

    extern int errno;
    /* Si se pasa un puerto por parametro se lo usa */
    if (argc > 1) port = atoi(argv[1]);
    /* Si no se pasa un puerto o es invalido uso 1500 */
    if (port == 0) port = 1500;

    Server* server = new Server();
    server->initialize_server(ip, port);

    cout << "Esperando conexion de cliente" << endl;
    /* La ejecucion se bloquea en este punto hasta que haya una conexion */
    /* El segundo parametro indica la cantidad de clientes maximos posibles */
    /* Escucho esperando al cliente */
    server->start_listening();

    server->accept_incoming_connections();

    cout << "Fin de los mensajes" << endl;
    /* LIBERA MEMORIA BOLUDO QUE SI ENTRA EN UN EXIT(1) SE CAGA TODO */

    server->shutdown();
    return 0;
}
