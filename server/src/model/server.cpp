#include "server.h"

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

#include "ClientConnection.h"

using namespace std;

Server::Server(string xmlConfigPath, string xmlLvlsConfigPath) {
    this->xmlConfigPath = xmlConfigPath;
    this->xmlLvlsConfigPath = xmlLvlsConfigPath;
    loadConfigs();
    this->scenery = new Scenery(&configs, 1); //El 1 es para que inicie en level 1
}

Server::~Server() {
    this->shutdownServer();
}

void sendConfigsToClient(int clientSocket, Server* server, SocketUtils& sockutils) {
    ConfigsXML configs = server->getConfigs();
    struct xmlConfig globalConf = configs.getGlobalConf();
    vector<struct xmlPlayer> players_sprites = configs.getPlayersConfig();
    vector<struct xmlEnemy> enemies_sprites = configs.getEnemiesConfig();
    vector<struct xmlBackground> backgrounds = configs.getBackgroundsConfig();

    sockutils.writeSocket(clientSocket, &globalConf, sizeof(struct xmlConfig));

    auto players_sprites_it = players_sprites.begin();
    while (players_sprites_it < players_sprites.end() - 1) {
        players_sprites_it->completion = EventCompletion::PARTIAL_MSG;
        sockutils.writeSocket(clientSocket, &(*players_sprites_it), sizeof(struct xmlPlayer));
        ++players_sprites_it;
    }
    /* Mando el último mensaje como FINAL */
    players_sprites_it->completion = EventCompletion::FINAL_MSG;
    sockutils.writeSocket(clientSocket, &(*players_sprites_it), sizeof(struct xmlPlayer));

    auto enemies_sprites_it = enemies_sprites.begin();
    while (enemies_sprites_it < enemies_sprites.end() - 1) {
        enemies_sprites_it->completion = EventCompletion::PARTIAL_MSG;
        sockutils.writeSocket(clientSocket, &(*enemies_sprites_it), sizeof(struct xmlEnemy));
        ++enemies_sprites_it;
    }
    /* Mando el último mensaje como FINAL */
    enemies_sprites_it->completion = EventCompletion::FINAL_MSG;
    sockutils.writeSocket(clientSocket, &(*enemies_sprites_it), sizeof(struct xmlEnemy));

    auto back_it = backgrounds.begin();
    while (back_it < backgrounds.end() - 1) {
        back_it->completion = EventCompletion::PARTIAL_MSG;
        sockutils.writeSocket(clientSocket, &(*back_it), sizeof(struct xmlBackground));
        ++back_it;
    }
    /* Mando el último mensaje como FINAL */
    back_it->completion = EventCompletion::FINAL_MSG;
    sockutils.writeSocket(clientSocket, &(*back_it), sizeof(struct xmlBackground));

}

/* Función para el thread de comunicación con el cliente
 * Manda los mensajes que se ingresen por cin()
 */
void client_comm(Server *srv, int client) {
    SocketUtils sockutils;
    /* Recibo user y pass del cliente */
    char user[20];
    recv(client, user, 20, 0); /* Nombre de usuario */
    Entity assignedPlayer = srv->connect_user(user);

    if (assignedPlayer != Entity::NOPLAYER) {
        /* Le informo al cliente que se logueo ok */
        struct event resp;
        resp.data.code = EventCode::LOGIN_OK;
        resp.data.id = assignedPlayer;
        sockutils.writeSocket(client, resp);

        sendConfigsToClient(client, srv, sockutils);

        ClientConnection* handler = new ClientConnection(client, srv, user);
        srv->add_connection(handler); /* El clientconnection se podría crear dentro de add_connection */
        handler->start();
        /* Le mando el estado actual del modelo al cliente */
        /* Tenemos forma de asegurar que el modelo haya empezado a correr cuando se llega a este punto? */
        srv->send_model_snapshot(handler);
    } else {
        struct event resp;
        resp.data.code = EventCode::LOGIN_FAIL;
        sockutils.writeSocket(client, resp);
    }
}

void Server::add_connection(ClientConnection *handler) {
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
    if (bind(listen_socket_fd, (struct sockaddr *) &server_addr, addr_size) < 0) {
        string error = strerror(errno);
        LOGGER_WRITE(Logger::ERROR, "Hubo un error al hacer el binding del socket: " + error, "Server.class")

        cout << "Hubo un error al hacer el binding del socket: " << error << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }
    return listen_socket_fd;
}

void Server::start_listening() {
    listen(listen_socket_fd, MAX_CONN);
}

void Server::shutdownServer() {
    LOGGER_WRITE(Logger::INFO, "Apagando Server", "Server.class")
    close_all_connections();
    shutdown(listen_socket_fd, 2);
    LOGGER_WRITE(Logger::INFO, "El server se a apagado", "Server.class")
}

void Server::accept_incoming_connections() {
    int client_id;
    struct sockaddr_in client_addr;
    socklen_t caddr_size;

    /* accept() devuelve un file descriptor asociado a la conexión con el cliente
        * y sólo a el */
    client_id = accept(listen_socket_fd, (struct sockaddr *) &client_addr,
                       &caddr_size);
    if (shouldClose) {
        cout << "Servidor cerrado" << endl;
        exit(1);
    }

    if (client_id < 0 and !shouldClose) {
        string error = strerror(errno);
        LOGGER_WRITE(Logger::INFO, "Hubo un error al conectar con el cliente: " + error, "Server.class")

        cout << "Hubo un error al conectar con el cliente: " << error << endl;
        cout << "Cerrando..." << endl;
        exit(1);
    }

    if (!shouldClose) {
        LOGGER_WRITE(Logger::INFO, "Ingresando cliente numero " + to_string(client_id), "Server.class")

        cout << "Ingresando cliente numero " << client_id << endl;
        client_comm(this, client_id);
        client_id++;
    }
}

int Server::close_connection(char *username) {
    /* responsabilidad de connectionHandler?
    * el es el dueño del socket después de todo
    */
    for (unsigned int i = 0; i < connections.size(); ++i) {
        if (strcmp(connections[i]->getUsername(), username) == 0) {
            connections[i]->stop();
            connections.erase(connections.begin() + i);
            break;
        }
    }
    return 0;
}

void Server::close_all_connections() {
    for (unsigned int i = 0; i < connections.size(); ++i) {
        close_connection(connections[i]->getUsername());
    }
}

vector<shared_ptr<ClientConnection> > Server::get_connections() {
    return connections;
}

void Server::handle_message(struct event event, EventCode code, char* username) {
    shared_ptr<ClientConnection> handler;
    /* Me llega un Evento y me tengo que fijar de quién viene */
    /* Tengo que pasarle al escenario el evento y el nombre de usuario que lo mandó */

    switch(code) {
    case EventCode::CLIENT_SEND_MSG:
        cout << "CLIENT_SEND_MSG" << endl;
        // store_message(message);
        break;

    case EventCode::CLIENT_DISCONNECT:
        cout << "CLIENT_DISCONNECT" << endl;
        handler = this->get_user_handler(username);
        this->incoming_events.push_back(event);
        close_connection(handler->getUsername());
        break;

    default:
        this->incoming_events.push_back(event);
        break;
    }
}

shared_ptr<ClientConnection> Server::get_user_handler(const char *username) {
    for (auto user : this->connections) {
        if (strcmp(user->getUsername(), username) == 0) {
            return user;
        }
    }
    return nullptr;
}

void Server::shouldCloseFunc(bool should) {
    shouldClose = should;
}

queue<struct event>* Server::getIncomingEvents() {
    // TODO lento! estas creando uan cola dentro de un while true por cada ciclo
    this->incoming_mutex.lock();
    queue<struct event>* ret = new queue<struct event>;
    for (auto event : incoming_events) {
        ret->emplace(event);
    }
    this->incoming_events.clear();
    this->incoming_mutex.unlock();
    return ret;
}

void Server::broadcast_event(struct event event) {
    for (auto client : connections) {
        client->queuemutex.lock();
        client->event_queue.push_back(event);
        client->queuemutex.unlock();
    }
}

Entity Server::connect_user(char* user) {
    string nombre_elegido;
    nombre_elegido.assign(user);
    return this->scenery->buildPlayer(nombre_elegido);
}

void Server::send_model_snapshot(ClientConnection* handler) {
    /* Aca tengo que usar lo que me devolvió process_keys_queue en su última
       corrida */
    handler->queuemutex.lock();
    for (auto event : last_model_snapshot) {
        handler->event_queue.push_back(event);
    }
    handler->queuemutex.unlock();
}

void Server::set_model_snapshot(vector<struct event> model_state) { this->last_model_snapshot = model_state;}

ConfigsXML& Server::getConfigs(){
    return configs;
}

void Server::loadConfigs(){
    XmlLoader loader(xmlConfigPath, xmlLvlsConfigPath);
    configs.setGlobalConf(loader.obtainGlobalConfig());
    configs.setBackgroundsConfig(loader.obtainBackgroundsConfig());
    configs.setPlayersConfig(loader.obtainPlayersConfig());
    configs.setEnemiesConfig(loader.obtainEnemiesConfig());
    configs.setLvlsConfig(loader.obtainLvlsConfig());
}

bool Server::enough_players_to_start() {
    return this->configs.getGlobalConf().cant_players == (int)this->connections.size();
}
