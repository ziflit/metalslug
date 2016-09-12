#include <iostream>
#include <thread>
#include "model/server.h"


void start_server_online(int argc, char* argv[], Server* server){
    /* Variables iniciales
     * int port: puerto en el cual el server escucha
     * int lserver_socket_fd: file desc. para el socket de listen
     * char buffer[BUFSIZE]: buffer para transferencia de mensajes
     * struct sockaddr_in client_addr: se guardan aca los datos del cliente conectado
    */
    int port = 0;
    string ip = "127.0.0.1";

    /* Si se pasa un puerto por parametro se lo usa */
    if (argc > 1) port = atoi(argv[1]);
    /* Si no se pasa un puerto o es invalido uso 1500 */
    if (port == 0) port = 1500;

    string path = "userslist.csv";
    if (argc > 2) string path = argv[2];


    server->initialize_server(ip, port);

    cout << "Esperando conexion de cliente" << endl;
    /* La ejecucion se bloquea en este punto hasta que haya una conexion */
    /* El segundo parametro indica la cantidad de clientes maximos posibles */
    /* Escucho esperando al cliente */
    server->start_listening();

    while (true) {
        server->accept_incoming_connections();
    }
}

int main(int argc, char* argv[]) {
    
    Server* server = new Server(path);

    std::thread server_online_in_thread;
    writer_thread = std::thread(start_server_online, argc, argv, server);
    writer_thread.detach();

    cout << "Servidor cerrado" << endl;
    server->shutdown();
    delete server;
    
    return 0;
}
