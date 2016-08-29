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

/* Dada una IP y un puerto arma una conexión con el servidor
 * generando un nuevo file descriptor de socket que se devuelve
 * al finalizar la conexión.
*/
int connect_to_server(string ip, int port) {
    int client_socket_fd;
    struct sockaddr_in server_addr;
    socklen_t server_sock_size;

    /* Abro el socket del cliente */
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0) {
        cout << "Error abriendo el socket del cliente: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }
    cout << "Conectado al servidor" << endl;

    socket_number = client_socket_fd;

    return 1;
}

int disconnect(){
    close(socket_number);
}

int send_message();

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

