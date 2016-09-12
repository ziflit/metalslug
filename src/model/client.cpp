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
    char response[MSGSIZE];

    recv(socket_number, response, MSGSIZE, 0);

    if(((msg_request_t*)response)->code == MessageCode::LOGIN_FAIL){
        cout << "Error conectando al servidor, datos ingresados incorrectos" << endl;
    }
    else {
        cout << "Autenticación OK. Conectado" << endl;
        strcpy(userName, user.data());
    }
    return 1;
}

void Client::disconnect(){
    close(socket_number);
}

int Client::send_message(int to, string content) {
    msg_request_t msg;
    string destinatedUser;
    msg.code = MessageCode::CLIENT_SEND_MSG;

    if ( to == usersList.size() ){
        send_message_to_all(content);
        return 0;
    } else {
        destinatedUser = searchUser(to);
    }

    strcpy(msg.message.msg, content.data());
    strcpy(msg.message.to, destinatedUser.data());
    strcpy(msg.message.from, userName);

    SocketUtils sockutils;
    sockutils.writeSocket(socket_number, msg);

    return 0;
}

void Client::send_message_to_all(string content) {
    int i;
    for ( i = 0 ; i < usersList.size() ; i++ ){
        send_message(i, content);
    }
}

int Client::receive_messages() {
    char buffer[MSGSIZE];
    SocketUtils sockutils;
    sockutils.readSocket(socket_number, buffer);
    struct msg_request_t recv_msg = *(struct msg_request_t*) buffer;
    cout << "Mensaje recibidos de: " << recv_msg.message.from << endl;
    cout << recv_msg.message.msg << endl;
}

void Client::lorem_ipsum(int frec, int max_envios) {
}

int Client::get_socket() {
    return socket_number;
}

void Client::show_users_list() {
    int i;
    for ( i = 0 ; i < usersList.size(); i++ ){
        cout << i << " - " << usersList[i] << endl;
    }
    cout << usersList.size() << " - All Users" << endl << endl;
}


void Client::ask_for_messages() {
    msg_request_t msg;
    msg.code = MessageCode::CLIENT_RECEIVE_MSGS;

    strcpy(msg.message.from, userName);
    SocketUtils sockutils;
    sockutils.writeSocket(socket_number, msg);
}


void Client::store_users_list(){
    /* Ace se va recibir la lista de usuarios, por el momento
     * hago una lista trucha
     */
    string user1, user2, user3;
    user1 = "santi";
    user2 = "fran";
    user3 = "lean";
    usersList.push_back(user1);   
    usersList.push_back(user2);
    usersList.push_back(user3);
}

string Client::searchUser(int user){
    return usersList[user];
}


