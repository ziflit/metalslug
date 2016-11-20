#include <iostream>
#include <unistd.h>

#include "model/client.h"
#include <time.h>
#include "utils/Logger.h"
#include "view/SDL/InitialWindow.h"
#include "view/SDL/SDLRunningGame.h"
#include "model/ClientHandler.h"
#include <thread>

using namespace std;

void enviarTeclasAlServer(Client* cliente, SDLRunningGame* sdlRunningGame){
    // Ciclo que envia teclas al server, cuando hay una tecla presionada o soltada.(nuevo keyevent)
    SDL_Event sdlEvent;
    while( cliente->is_connected()){
        while (SDL_PollEvent( &sdlEvent )) {
            if ( sdlEvent.type == SDL_QUIT ) {
                cliente->disconnect();
                break;
            }
            struct event nuevoEvento = sdlRunningGame->eventsHandler(&sdlEvent); //El eventsHandler envia los mensajes al Server
            if(not (nuevoEvento.data.code == EventCode::TODO_SIGUE_IGUAL)){
                cliente->getHandler()->sendEvent(nuevoEvento);

            }
        }
        usleep(1000);
    }
}


int main(int argc, char *argv[]) {
/* Seteo puerto e ip del server*/
LOGGER_START(Logger::INFO, "client.log")
int port = 0;
string ip = "127.0.0.1";


/* Creo al cliente */
Client *cliente = new Client();

/* Configuracion del puerto
 * atoi() devuelve 0 si el parametro es invalido*/
if (argc > 1) port = atoi(argv[1]);
if (port == 0) port = 1500;
if (argc > 2) ip = argv[2];

string user;
cout << "Ingrese nombre de usuario: " << endl;
cin >> user;



    InitialWindow* initialWindow = new InitialWindow(800, 600);
    initialWindow->showStartScreen();

if (not cliente->is_connected()) {
    LOGGER_WRITE(Logger::INFO, "Estableciendo la conexion con el servidor...", "ClientMain")
    cout << "Estableciendo la conexion con el servidor..." << endl << endl;
    if (cliente->connect_to_server(ip, port, user)) {
        cliente->set_connection_status(true);
        LOGGER_WRITE(Logger::INFO, "Conexion con el servidor establecida con exito.", "ClientMain")
        cout << " Conexion establecida con exito " << endl << endl;
    } else {
        cliente->set_connection_status(false);
    }
}
//____________________________________________________________________________________________

if (cliente->is_connected()){

    SDLRunningGame* sdlRunningGame = new SDLRunningGame(initialWindow->getMainWindow(),initialWindow->getMainRenderer(),cliente->getConfigs());

    /* Una vez que tengo SDL cargado, se avisa al servidor y se inicia el
     handler para el envío y recepción de mensajes */
    cliente->start_connection();

    thread enviarTeclasAlServerEnThread;
    enviarTeclasAlServerEnThread = thread(enviarTeclasAlServer, cliente, sdlRunningGame);

    // Ciclo que recive constantemente el estado del escenario, y se lo manda al sdlRunningGame para que lo dibuje
    vector<struct event> modelStateToRender;

    int count = 0;
    double time_counter = 0;

    clock_t now = clock();
    clock_t last = now;

    while(cliente->is_connected()){
        now = clock();

        time_counter += double(now - last);
        last = now;

        modelStateToRender = (cliente->getHandler())->getModelState();
        if (not modelStateToRender.empty()){
            count++;
            if (time_counter > (double)CLOCKS_PER_SEC) {
                cout << count << endl;
                time_counter -= (double)CLOCKS_PER_SEC;
            }
            sdlRunningGame->handleModelState(modelStateToRender);
        }
        double tiempo_a_dormir = (double)now + 25000 - (double)clock();
        if ((tiempo_a_dormir) > 0) {
            usleep (tiempo_a_dormir);
        }
    }
    enviarTeclasAlServerEnThread.join();
}

delete cliente;
return 0;
}
