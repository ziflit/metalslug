#include <iostream>
#include "model/client.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]) {
    /* Seteo puerto e ip del server*/
    int port = 0;
    string ip = "127.0.0.1";

    /* Creo al cliente */
    Client* cliente1 = new Client();

    /* Para el manejo de errores */
    extern int errno;

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido*/
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    /* Menu de cliente */

    bool endloop=false, conectado=false;
    char keypressed;
 
    do{
        cin.clear();
        cout << "*-----------------------*" << endl;
        cout << "! Bienvenido al cliente !" << endl;
        cout << "*-----------------------*" << endl << endl;
        cout << "\t1 .- Conectar al servidor" << endl;
        cout << "\t2 .- Enviar Mensaje" << endl;
        cout << "\t3 .- Chequear mensajes" << endl;
        cout << "\t4 .- Desconectar" << endl;
        cout << "\t5 .- Lorem Ipsum" << endl;
        cout << "\t6 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
 
        cin >> keypressed;
 
        switch(keypressed)
        {
            case '1':
                cin.clear();
                cout << "Estableciendo la conexion con el servidor...\n";
                    cliente1->connect_to_server(ip, port);
                    cliente1->receive_messages();
                    conectado = true;
                break;
 
            case '2':
                cin.clear();
                    if (conectado) {
                    cout << "*-----------------------*" << endl;
                    cout << "!    Envio de mensajes   !" << endl;
                    cout << "*-----------------------*" << endl << endl;
                    cout << "Elija el destinatario" << endl << endl;
                    /*aca va la logica de como elegir el destinatario
                     * para poder armar el mensaje a enviar*/
                    Message* mensaje = new Message(1,"from","to","content of test message");
                    delete mensaje;
                    break;    
                    }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;
 
            case '3':
                cin.clear();
                if (conectado) {    
                    cout << "Solicitando mensajes al servidor...\n";
                    cliente1->receive_messages();
                    /*hay que ver si receive messages los muestra directamente por
                     *pantalla o lo hacemos aca*/
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;

            case '4':
                cin.clear();
                if (conectado) {
                    cliente1->disconnect();
                    cout << "Ud. Se ha desconectado del servidor\n";
                    conectado = false;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;

             case '5':
                cin.clear();
                if (conectado) {
                    cout << "*-----------------------*" << endl;
                    cout << "!      Lorem Ipsum      !" << endl;
                    cout << "*-----------------------*" << endl << endl;

                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;


            case '6':
                endloop=true;
                delete cliente1;
                break;


            default:
                cin.clear();
                cout << "Opcion no valida.\a\n";
                break;
        }
    }while(endloop!=true);

    
    return 0;
}
