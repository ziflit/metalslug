#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include "server.h"
#include "ClientConnection.h"

using namespace std;

Server::Server(string path) {
    this->userloader = new UserLoader(path);
}

Server::~Server() {
    this->shutdown();
}

/* Función para el thread de comunicación con el cliente
 * Manda los mensajes que se ingresen por cin()
 */
void client_comm(Server* srv, int client) {
    /* Mensaje de bienvenida. Se manda una vez fijo */

    SocketUtils sockutils;
    /* Recibo user y pass del cliente */
    char user[20];
    char pass[20];
    recv(client, user, 20, 0);
    recv(client, pass, 20, 0);
    if (srv->auth_user(user, pass)) {
        struct msg_request_t resp;
        resp.code = MessageCode::LOGIN_OK;

        sockutils.writeSocket(client, resp);

        ClientConnection* handler = new ClientConnection(client, srv, user);
        handler->start();
        srv->add_connection(handler);
    } else {
        struct msg_request_t resp;
        resp.code = MessageCode::LOGIN_FAIL;
        sockutils.writeSocket(client, resp);
    }
    /* Esto crea un nuevo objeto ClientConnection que
     * se comunicará con el cliente en cuestión. Le paso el fd */
}

bool Server::auth_user(char* user, char* pass) {
    return true;
}

void Server::add_connection(ClientConnection* handler) {
    /* No usar nunca más el puntero pelado luego de esta
       llamada a emplace_back */
    connections.emplace_back(handler);
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
    return listen_socket_fd;
}

void Server::start_listening() {
    listen(listen_socket_fd, MAX_CONN);
}

void Server::shutdown() {
    delete userloader;
    close_all_connections();
    close(listen_socket_fd);
}

void Server::accept_incoming_connections() {
    int client_id;
    struct sockaddr_in client_addr;
    socklen_t caddr_size;

    /* accept() devuelve un file descriptor asociado a la conexión con el cliente
        * y sólo a el */
    client_id = accept(listen_socket_fd, (struct sockaddr*)&client_addr,
                                &caddr_size);
    if (client_id < 0) {
        cout << "Hubo un error al conectar con el cliente: " << strerror(errno) << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }

    cout << "Ingresando cliente numero" << client_id << endl;
    client_comm(this, client_id);
    client_id++;
}

int Server::close_connection(char* username) {
    /* responsabilidad de connectionHandler?
    * el es el dueño del socket después de todo
    */
    for (unsigned int i = 0; i < connections.size(); ++i) {
        if (strcmp(connections[i]->getUsername(), username) == 0) {
            connections.erase(connections.begin() + i);
            break;
        }
    }
    return 0;
}

void Server::close_all_connections() {
    for (unsigned int i = 0; i < connections.size(); ++i) {
        connections[i]->stop();
    }
}

vector<shared_ptr<ClientConnection> > Server::get_connections() {
    return connections;
}

void filter_and_send(Server* server, char* requester, shared_ptr<ClientConnection> handler) {
    // auto realmessages = server->get_messages_of(requester);

    std::list<msg_t> messages;
    struct msg_t dummy;
    strcpy(dummy.from, "santi");
    strcpy(dummy.to, "santi");
    strcpy(dummy.msg, "saraza");
    messages.push_back(dummy);

    /* Consigo el handler del usuario que pide y le agrego
       los mensajes para mandar */
    struct msg_request_t full_msg;
    /* Cuando le seteo el código en realidad voy a estar poniendo
        si es final o no */
    full_msg.code = MessageCode::CLIENT_SEND_MSG;
    full_msg.message = messages.front();
    handler->push_event(full_msg);
}

void Server::handle_message(struct msg_request_t message) {
    shared_ptr<ClientConnection> handler;
    std::thread writer_thread;
    switch(message.code){
        case MessageCode::CLIENT_SEND_MSG:
            cout << "CLIENT_SEND_MSG" << endl;
            store_message(message.message);
            break;

        case MessageCode::CLIENT_RECEIVE_MSGS:
            cout << "CLIENT_RECEIVE_MSGS" << endl;
            /* Aca hay que hacer la parte de enviar todos los
             * mensajes que hay en la lista al usuario en cuestion
             * deberia estar en un thread aparte */
            handler = this->get_user_handler(message.message.from);
            writer_thread = std::thread(filter_and_send, this, message.message.from, handler);
            writer_thread.detach();
            break;

        default:
            string content;
            content.assign(message.message.msg);
            cout << "El mensaje entrante es: " << content << endl;
            break;
    }
}

std::shared_ptr<ClientConnection> Server::get_user_handler(char* username) {
    for (auto user : this->connections) {
        if (strcmp(user->getUsername(), username) == 0) {
            return user;
        }
    }
    return nullptr;
}

void Server::store_message(const msg_t& mensaje) {
    messagesList.push_back(mensaje);
}

std::list<msg_t> Server::get_messages_of(char* user){
    std::list<msg_t> messagesFiltered;
    for (auto it = messagesList.begin(); it != messagesList.cend();){
        if(strcmp(it->to, user) == 0){
            messagesFiltered.push_back(*it);
            it = messagesFiltered.erase(it); // ...
        } else {
            it++;
        }
    }
    return messagesFiltered;
}
/* Si  necesito acceso aleatorio, uso vector
pero si necesito recorrer de principio a fin o voy borrando/insertando
elementos en el medio, uso list */
