#include <iostream>
#include <thread>
#include <unistd.h>
#include <time.h>

#include "model/server.h"
#include "utils/Logger.h"

const int FPS = 30;
bool onlinethread = true;

void clearQueue( queue<struct event> &q ){ // para borrar la cola de forma eficiente
   queue<struct event> empty;
   std::swap( q, empty );
}

void correr_modelo(Server* server) {
    /* Ya no es tan dummy esto:

       1. Levanto el XML que corresponde al escenario
       2. Empiezo a escuchar conexiones hasta el límite indicado en el paso anterior
       3. Una vez que llego al límite de conexiones (o al mínimo necesario) comienzo el gameloop
       4. El loop: cuando se empieza el loop se cuentan con las siguientes cosas:
        a) Clientes conectados con sus respectivos handlers
        b) El modelo ya está creado (no empezó a correr aún)
        La función del loop es desacolar eventos y procesarlos modelo por medio
        vaciamos la cola de mensajes entrantes y los procesamos en el orden de llegada por el modelo.
        Es más eficiente darle al modelo una cola entera de mensajes, posiblemente desde referencia en el
        servidor, que pasarle uno por uno los eventos que llegaron.

    */
    int count = 0;
    double time_counter = 0;

    useconds_t ms_per_frame = 32000;
    clock_t start = clock();
    clock_t last = start;

    queue<struct event>* eventos;
    vector<struct event> model_state;
    while (onlinethread) {
        start = clock();
        time_counter += double(start - last);
        /* genero una copia de todos los eventos, libero la cola para que se pueda seguir usando y
           le paso la copia (o refernecia, no se) al modelo */
        eventos = server->getIncomingEvents();
        model_state = server->getScenery()->process_keys_queue(eventos);
        server->set_model_snapshot(model_state);
        for (auto state : model_state) {
            server->broadcast_event(state);
        }
        if (time_counter > (double)CLOCKS_PER_SEC) {
            cout << count << endl;
            time_counter -= (double)CLOCKS_PER_SEC;
        }
        count++;
        delete eventos;
        double lalala = (double)start + (double)ms_per_frame - (double)clock();
        last = clock();
        if ((lalala) > 0) {
            usleep (lalala);
        }
        if (not eventos->empty())
        clearQueue(*eventos); //borra la cola de forma eficiente
        model_state.clear();
    }

    delete eventos;
}

void start_server_online(Server* server, string ip, int port){

    server->initialize_server(ip, port);

    cout << "Esperando conexion de cliente" << endl;
    /* La ejecucion se bloquea en este punto hasta que haya una conexion */
    /* El segundo parametro indica la cantidad de clientes maximos posibles */
    /* Escucho esperando al cliente */
    server->start_listening();

    while (onlinethread) {
        server->accept_incoming_connections();
        cout << "Onlinethread" << endl;
    }


}

int main(int argc, char* argv[]) {
    LOGGER_START(Logger::INFO, "server.log")
    int port = 0;
    // string ip = "10.251.45.50";
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

    thread corredor_de_modelo = std::thread(correr_modelo, server);
    corredor_de_modelo.detach();

    bool online = true;
    while (online) {
        std::string keypressed;
        getline(std::cin, keypressed);
        if (keypressed == "q") {
            LOGGER_WRITE(Logger::INFO, "Apagando el servidor...", "ClientMain")
            online = false;
            server->shouldCloseFunc(true);            
        }
        sleep(2);
    }
    onlinethread = false;
    server->shutdownServer();
    server_online_in_thread.join();
    delete server;

    return 0;
}
