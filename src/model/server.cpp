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
#include "message.h"

using namespace std;

/* Función para el thread de comunicación con el cliente
 * Manda los mensajes que se ingresen por cin()
 */
void* Server::client_comm(void* client) {
    /* Mensaje de bienvenida. Se manda una vez fijo */
    string message;
    int client_id = *(int*)client;

    message = "Estás conectado! Bienvenido!";
    send(client_id, message.data(), BUFSIZE, 0);

    char buffer[BUFSIZE];
    int msg_size =  recv(client_id, &buffer, BUFSIZE, 0);
    message.assign(buffer);

    /* Checkeo estupido para probar algo que Fran me mandaba */
    if (message.find("vieja") != string::npos) {
        cout << "Me llegó tu vieja en tanga, piola" << endl;
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

    for (int i=0; i < MAX_CONN; ++i) {
        clients[i] = 0;
    }
    return listen_socket_fd;
}

void Server::start_listening() {
    listen(listen_socket_fd, MAX_CONN);
}

void Server::shutdown() {
    close_all_connections();
    close(listen_socket_fd);
}

void Server::accept_incoming_connections() {
    int client_id = -1;
    for (int i=0; i < MAX_CONN; ++i) {
        if (clients[i] == 0) {
            client_id = i;
            break;
        }
    }
    // No hay conexiones disponibles
    // Debería esperar hasta que haya una
    if (client_id == -1) {
        cout << "No hay más conexiones disponibles" << endl;
        for (int i=0; i < MAX_CONN; ++i) {
            cout << clients[i] << endl;
        }
        return;
    }

    struct sockaddr_in client_addr;
    socklen_t caddr_size;

    /* accept() devuelve un file descriptor asociado a la conexión con el cliente
        * y sólo a el */
    clients[client_id] = accept(listen_socket_fd, (struct sockaddr*)&client_addr,
                                &caddr_size);
    if (clients[client_id] < 0) {
        cout << "Hubo un error al conectar con el cliente: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }

    cout << "Ingresando cliente numero" << client_id << endl;
    pthread_create(&th_clientes[client_id], NULL, client_comm, (void*) &clients[client_id]);
    client_id++;
}

int Server::close_connection(int client_id) {
    if (close(clients[client_id]) != 0) {
        //Log
        return -1;
    }
    pthread_join(th_clientes[client_id], NULL);
    clients[client_id] = 0; /* Libero el slot de cliente */
    return 0;
}

void Server::close_all_connections() {
    for (int i=0; i<MAX_CONN; ++i) {
        close_connection(i);
    }
}

int* Server::get_connections() {
    return clients;
}
