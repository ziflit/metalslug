#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char* argv[]) {

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
    int client_socket_fd;
    struct sockaddr_in server_addr;
    socklen_t server_sock_size;

    /* Para el manejo de errores */
    extern int errno;

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido
    */
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    /* Abro el socket del cliente */
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0) {
        cout << "Error abriendo el socket del cliente: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }
    /* Configuro las direcciones del cliente */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.data());

    server_sock_size = sizeof(server_addr);

    /* Me conecto al servidor. Devuelve -1 si la conexion falla */
    if (connect(client_socket_fd, (struct sockaddr *)&server_addr, server_sock_size) < 0) {
        cout << "Error conectando al servidor: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }
    cout << "Conectado al servidor" << endl;

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
    close(client_socket_fd);

    return 0;
}
