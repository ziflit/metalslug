#include <iostream>
#include "model/client.h"

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
    int bufsize = 1024;
    char buffer[bufsize];

    Client cliente1;

    /* Para el manejo de errores */
    extern int errno;

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido
    */
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    

    cliente1.connect_to_server(ip, port);
    cliente1.send_message();
    

    /* Se considera el fin de las comunicaciones si no hay
     * ningún nuevo mensaje para recibir, es decir que el servidor
     * no manda más nada y probablemente cerró la conexión
    */
    int msg_size; /* Va a guardar la cantidad de bytes leidos por recv */
    bool endofcomm = false;
    while (!endofcomm) {
        msg_size = recv(client_socket_fd, &buffer, bufsize, 0);
        if (msg_size == 0) { /* si recv devuelve 0 bytes no hay mensaje */
            endofcomm = true;
            break;
        }
        cout << buffer << endl;
    }
    cout << "Fin de los mensajes" << endl;
    cliente1.disconnect();

    return 0;
}



}
