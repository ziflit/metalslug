#include <iostream>
#include <thread>

#include "model/server.h"
#include "utils/Logger.h"

bool onlinethread = true;

void start_server_online(Server* server, string ip, int port){

    server->initialize_server(ip, port);

    cout << "Esperando conexion de cliente" << endl;
    /* La ejecucion se bloquea en este punto hasta que haya una conexion */
    /* El segundo parametro indica la cantidad de clientes maximos posibles */
    /* Escucho esperando al cliente */
    server->start_listening();

    while (onlinethread) {
        server->accept_incoming_connections();
        cout << onlinethread << endl;
    }

}

int main(int argc, char* argv[]) {
    LOGGER_START(Logger::INFO, "server.log")
    int port = 0;
    string ip = "127.0.0.1";

    /* Si se pasa un puerto por parametro se lo usa */
    if (argc > 1) port = atoi(argv[1]);
    /* Si no se pasa un puerto o es invalido uso 1500 */
    if (port == 0) port = 1500;

    string path = "userslist.csv";
    if (argc > 2) string path = argv[2];

    Server* server = new Server(path);
    server->shouldCloseFunc(false);

    std::thread server_online_in_thread;
    server_online_in_thread = std::thread(start_server_online, server, ip, port);

    bool online = true;
    while (online) {
        std::string keypressed;
        getline(std::cin, keypressed);
        if (keypressed == "q") {
            LOGGER_WRITE(Logger::INFO, "Apagando el servidor...", "ClientMain")

            online = false;
            server->shouldCloseFunc(true);            
        }
    }
    onlinethread = false;
    server->shutdownServer();
    server_online_in_thread.join();
    delete server;

    return 0;
}
