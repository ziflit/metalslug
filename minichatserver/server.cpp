#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    /* Variables iniciales
     * int port: puerto en el cual el server escucha
     * int lserver_socket_fd: file desc. para el socket de listen
     * int cserver_socket_fd: file desc. para el socket conectado con el cliente
     * int bufsize: tamano maximo de mensaje
     * char buffer[bufsize]: buffer para transferencia de mensajes
     * struct sockaddr_in server_addr: datos para la conexion del socket
    */
    int port = 0;
    int lserver_socket_fd;
    int cserver_socket_fd;
    int bufsize = 1024;
    char* ip = "127.0.0.1";
    char buffer[bufsize];
    string message;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_size;
    socklen_t caddr_size;

    extern int errno;
    /* Si se pasa un puerto por parametro se lo usa */
    if (argc > 1) port = atoi(argv[1]);
    /* Si no se pasa un puerto o es invalido uso 1500 */
    if (port == 0) port = 1500;

    /* Creo el primer socket
     * AF_INET indica IPv4
     * SOCK_STREAM indica tipo de socket de stream binario
     * IPPROTO_TCP indica TCP
    */
    lserver_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lserver_socket_fd < 0) {
        cout << "\nError en la creacion del socket" << endl;
        exit(1);
    }
    /* Configuro los datos del servidor
     * Para enviarlos al socket
    */
    server_addr.sin_family = AF_INET;
    /* inet_addr() transforma el string en el unsigned long que espera s_addr */
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    addr_size = sizeof(server_addr);

    /* Asigno el nombre al socket usando bind():
     * es decir, le asigno una direccion
    */
    if (bind(lserver_socket_fd, (struct sockaddr*)&server_addr, addr_size) < 0) {
        cout << "Hubo un error al hacer el binding del socket: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
    }

    /* Escucho esperando al cliente */
    cout << "Esperando conexion de cliente" << endl;
    /* La ejecucion se bloquea en este punto hasta que haya una conexion */
    listen(lserver_socket_fd, 1);

    /* Cuando ya tenemos una conexion entrante tenemos que aceptarla
     * en cserver_socket_fd se guarda un nuevo socketfd desde donde voy a
     * recibir y mandar los mensajes. accept() devuelve -1 si hay errores.
    */
    cserver_socket_fd = accept(lserver_socket_fd,
                               (struct sockaddr*)&client_addr,
                               &caddr_size);
    if (cserver_socket_fd < 0) {
        cout << "Hubo un error al conectar con el cliente: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }

    /* Aca va la logica de envio y recepcion de mensajes */
    message = "Estás conectado! Bienvenido!";
    send(cserver_socket_fd, message.data(), message.size(), 0);

    /* cserver_socket_fd debe cerrarse cuando se pierde la conexion con el cliente */
    close(cserver_socket_fd);
    close(lserver_socket_fd);
    return 0;
}
