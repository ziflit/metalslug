#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "client.h"
#include "message.h"
#include "../Utils/Protocol.h"

using namespace std;


int Client::connect_to_server(string ip, int port) {
    struct sockaddr_in server_addr;
    socklen_t server_sock_size;

    /* Abro el socket del cliente */
    socket_number = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_number < 0) {
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
    if (connect(socket_number, (struct sockaddr *)&server_addr, server_sock_size) < 0) {
        cout << "Error conectando al servidor: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(EXIT_FAILURE);
    }


    string user;
    string pass;

    cout << "Ingrese nombre de usuario: " << endl;
    cin >> user;
    cout << "Ingrese contrasenia: " << endl;
    cin >> pass;

    /*Envio mje al servidor*/
    send(socket_number,user.data(),40,0);
    send(socket_number,pass.data(),40,0);
    char* response;
    unsigned int size;

    recv(socket_number, (void*)&size, sizeof(unsigned int),0);
    recv(socket_number, response, size, 0); // devuelve un int con la cantidad de bytes leidos

    if(((msg_request_t*)response)->code == MessageCode::LOGIN_FAIL){
        cout << "Error conectando al servidor, datos ingresados incorrectos" << endl;
    }
    else{
        cout << "LOG OK GATO" << endl;
    }

    cout << "saliendo de la fn" <<endl;

    return 1;
}

void Client::disconnect(){
    close(socket_number);
}

int Client::send_message(Message* msg){
    send(socket_number, (msg->serialize()).data(), BUFSIZE, 0);
    return 0;
}


int Client::receive_messages() {

    char buffer[BUFSIZE];

    recv(get_socket(), &buffer, BUFSIZE, 0);
    cout << buffer << endl;
    if (buffer=="ENDOFMESSAGES,,,"){return 1;}
    return 0;
}


void Client::lorem_ipsum(int frec, int max_envios) {
}

int Client::get_socket() {
    return socket_number;
}
