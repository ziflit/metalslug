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
        return 0;
    }
    /* Configuro las direcciones del cliente */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.data());

    server_sock_size = sizeof(server_addr);

    /* Me conecto al servidor. Devuelve -1 si la conexion falla */
    if (connect(socket_number, (struct sockaddr *)&server_addr, server_sock_size) < 0) {
        cout << "Error conectando al servidor: " << strerror(errno) << endl;
        return 0;
    }


    string user;
    string pass;

    cout << "Ingrese nombre de usuario: " << endl;
    cin >> user;
    cout << "Ingrese contrasenia: " << endl;
    cin >> pass;

    /*Envio mje al servidor*/
    cout << send(socket_number,user.data(),20,0) << endl;
    cout << send(socket_number,pass.data(),20,0) << endl;
    char* response;
    unsigned int size;

    recv(socket_number, (void*)&size, sizeof(unsigned int),0);
    recv(socket_number, response, size, 0);

    if(((msg_request_t*)response)->code == MessageCode::LOGIN_FAIL){
        cout << "Error conectando al servidor, datos ingresados incorrectos" << endl;
    }
    else {
        cout << "Autenticación OK. Conectado" << endl;
    }
    return 1;
}

void Client::disconnect(){
    close(socket_number);
}

int Client::send_message(string to, string content) {
    msg_request_t msg;
    msg.code = MessageCode::CLIENT_SEND_MSG;
    strcpy(msg.message.msg, content.data());
    strcpy(msg.message.to, to.data());
    strcpy(msg.message.from, me.data());

    SocketUtils sockutils;
    sockutils.writeSocket(socket_number, msg);

    return 0;
}

void Client::send_message_to_all() {

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

void Client::show_users_list() {
    int i;
    for ( i = 0 ; usersList.size() ; i++ ){
        cout << i << " - " << usersList[i] << endl;
    }
    cout << i + 1 << endl;
}

void Client::send_message_to(int userSelected) {
    if ( userSelected == (usersList.size() + 1) ){
        send_message_to_all();
        return ;
    }
    
}

void Client::ask_for_messages() {

}


