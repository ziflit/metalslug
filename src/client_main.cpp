#include <iostream>
#include "model/client.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]) {

    /* Variables iniciales
     * int port: Puerto al cual me voy a conectar
     * char* ip: IP del servidor
     * int bufsize: tamaño del buffer de mensajes
     * char buffer[bufsize]: buffer para mensajes
     * int client_socket_fd: file desc. para el socket del cliente
     * struct sockaddr_in client_addr: datos del socket de conexion
    */
    int port = 0;
    string ip = "127.0.0.1";


    Client* cliente1 = new Client();
    Message* mensaje = new Message(1,"from","to","content of test message");

    /* Para el manejo de errores */
    extern int errno;

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido
    */
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    cliente1->connect_to_server(ip, port);
    cliente1->receive_messages();
    cliente1->disconnect();

    delete cliente1;
    delete mensaje;

    return 0;
}
