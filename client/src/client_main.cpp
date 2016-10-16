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
            if ( sdlEvent.type == SDL_QUIT) {
                cliente->disconnect();
                break;
            }
            struct event nuevoEvento = sdlRunningGame->eventsHandler(&sdlEvent); //El eventsHandler envia los mensajes al Server
            if(not (nuevoEvento.data.code == EventCode::TODO_SIGUE_IGUAL)){
                cliente->getHandler()->sendEvent(nuevoEvento);

            }
        }
        usleep(100);
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


// Conexion con el server
if (not cliente->is_connected()) {
    LOGGER_WRITE(Logger::INFO, "Estableciendo la conexion con el servidor...", "ClientMain")
    cout << "Estableciendo la conexion con el servidor..." << endl << endl;
    cout << "Ingrese su nombre de usuario: ";
    if (cliente->connect_to_server(ip, port)) {
        cliente->set_connection_status(true);
        LOGGER_WRITE(Logger::INFO, "Conexion con el servidor establecida con exito.", "ClientMain")
        cout << " Conexion establecida con exito " << endl << endl;
    } else {
        cliente->set_connection_status(false);
    }
}
//____________________________________________________________________________________________

if (cliente->is_connected()){

    InitialWindow* initialWindow = new InitialWindow(800, 600);
    SDLRunningGame* sdlRunningGame = new SDLRunningGame(initialWindow->getMainWindow(),initialWindow->getMainRenderer());

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
        double lalala = (double)now + 25000 - (double)clock();
        if ((lalala) > 0) {
            usleep (lalala);
        }
    }
    enviarTeclasAlServerEnThread.join();
}

delete cliente;
return 0;
}





    






//    do {
//        cout << "*-----------------------*" << endl;
//        cout << "! Bienvenido al cliente !" << endl;
//        cout << "*-----------------------*" << endl << endl;
//        if (!cliente1->is_connected()) {
//            cout << "\t1 .- Conectar al servidor" << endl;
//        }
//        if (cliente1->is_connected()) {
//            cout << "\t2 .- Enviar Mensaje" << endl;
//            cout << "\t3 .- Chequear mensajes" << endl;
//            cout << "\t4 .- Desconectar" << endl;
//            cout << "\t5 .- Lorem Ipsum" << endl;
//        }
//        cout << "\t6 .- Salir" << endl << endl;
//        cout << "Elije una opcion: ";
//
//        cin >> keypressed;
//
//        switch (keypressed) {
//
//            case '1':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                if (!cliente1->is_connected()) {
//                    LOGGER_WRITE(Logger::INFO, "Estableciendo la conexion con el servidor...", "ClientMain")
//                    cout << "Estableciendo la conexion con el servidor..." << endl << endl;
//                    if (cliente1->connect_to_server(ip, port)) {
//
//                        cliente1->set_connection_status(true);
//                        cout << "\033[2J\033[1;1H"; /* clear screen */
//                        LOGGER_WRITE(Logger::INFO, "Conexion con el servidor establecida con exito.", "ClientMain")
//                        cout << " Conexion establecida con exito " << endl << endl;
//                        break;
//                    } else {
//                        cliente1->set_connection_status(false);
//                        break;
//                    }
//
//                }
//                LOGGER_WRITE(Logger::INFO, "El cliente ya se encontraba conectado con el servidor", "ClientMain")
//                cout << " Ud. ya se encuentra conectado al servidor " << endl << endl;
//                break;
//
//
//            case '2':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                if (cliente1->is_connected()) {
//                    int userSelected;
//                    string contentMsg;
//
//                    cout << "*-----------------------*" << endl;
//                    cout << "!    Envio de mensajes   !" << endl;
//                    cout << "*-----------------------*" << endl << endl;
//                    cliente1->show_users_list();  /* implementar esto */
//
//                    cout << "Elija el destinatario: ";
//                    cin >> userSelected;
//
//                    cout << "Escriba el mensaje a enviar: " << endl;
//                    cin.ignore();
//                    getline(cin, contentMsg);
//
//                    cout << "\033[2J\033[1;1H"; /* clear screen */
//                    cout << "El mensaje fue enviado con exito. " << endl;
//                    LOGGER_WRITE(Logger::INFO, "Enviando mensaje a " + userSelected, "ClientMain")
//                    cliente1->send_message(userSelected, contentMsg);
//
//                    break;
//                }
//                cout << "Por favor, primero conectese al servidor" << endl << endl;
//                break;
//
//
//            case '3':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                if (cliente1->is_connected()) {
//                    LOGGER_WRITE(Logger::INFO, "Pidiendo mensajes al servidor.", "ClientMain")
//
//                    cout << "Solicitando mensajes al servidor..." << endl << endl;
//                    /* Enviar mensaje especial al server para que
//                    * sepa que le estoy pidiendo los mensajes, el mensaje
//                    * especial, debe tener al usuario en cuestion */
//                    // Message* mensaje = new Message(GETUSERMESSAGES,"","","");
//                    // cliente1->send_message(mensaje) ;
//                    cliente1->ask_for_messages(); /* implementar esto */
//
//                    if (cliente1->receive_messages() == -1) {
//                        cliente1->set_connection_status(false);
//                    };
//                    LOGGER_WRITE(Logger::INFO, "Conexion con el servidor establecida con exito.", "ClientMain")
//
//                    // delete mensaje;
//                    break;
//                }
//
//                cout << "Por favor, primero conectese al servidor" << endl << endl;
//                break;
//
//
//            case '4':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                if (cliente1->is_connected()) {
//                    cliente1->disconnect();
//                    cout << "Ud. Se ha desconectado del servidor" << endl << endl;
//                    cliente1->set_connection_status(false);
//                    break;
//                }
//                cout << "Por favor, primero conectese al servidor" << endl << endl;
//                break;
//
//
//            case '5':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                if (cliente1->is_connected()) {
//                    long max_sends, frequency;
//                    cout << "*-----------------------*" << endl;
//                    cout << "!      Lorem Ipsum      !" << endl;
//                    cout << "*-----------------------*" << endl << endl;
//
//                    cout << "Ingrese la frecuencia deseada:" << endl;
//                    cin >> frequency;
//
//                    cout << "Ingrese la cantidad de mensajes a enviar:" << endl;
//                    cin >> max_sends;
//
//                    char *path = "src/Utils/arch.txt";
//                    LoremIpsum *lorem = new LoremIpsum(frequency, max_sends, path, cliente1);
//                    lorem->iniciar();
//
//                    break;
//                }
//                LOGGER_WRITE(Logger::INFO, "Cliente debe estar conectado para poder enviar mensajes", "ClientMain")
//                cout << "Por favor, primero conectese al servidor" << endl << endl;
//                break;
//
//
//            case '6':
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                endloop = true;
//                LOGGER_WRITE(Logger::INFO, "Desconectando Cliente.", "ClientMain")
//
//                if (cliente1->is_connected()) {
//                    cliente1->disconnect();
//                }
//                cliente1->set_connection_status(false);
//                LOGGER_WRITE(Logger::INFO, "Se ha desconectado el cliente exitosamente.", "ClientMain")
//
//                break;
//
//
//            default:
//                cout << "\033[2J\033[1;1H"; /* clear screen */
//                cout << "Opcion no valida." << endl << endl;
//                break;
//        }
//    } while (!endloop);


//    sdlRunningGame.~SDLRunningGame();
