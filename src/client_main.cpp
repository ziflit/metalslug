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

    /* Configuracion del puerto
     * atoi() devuelve 0 si el parametro es invalido*/
    if (argc > 1)  port = atoi(argv[1]);
    if (port == 0) port = 1500;

    /* Menu de cliente */

    bool endloop=false, conectado=false;
    char keypressed;
 
    do{
        // cout << "\033[2J\033[1;1H";
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
                if (!conectado) {
                cout << "Estableciendo la conexion con el servidor..." << endl << endl;
                    if (cliente1->connect_to_server(ip, port) ==  1 ){
                        conectado = true;
                    } else {
                        break;
                    }
                    /* Implementar logueo de usuario */

                    /* Recibir lista de usuarios en el servidor */

                    
                }
                cout << " Ud. ya se encuentra conectado al servidor " << endl << endl;
                break;
 


            case '2':
                if (conectado) {
                    cout << "*-----------------------*" << endl;
                    cout << "!    Envio de mensajes   !" << endl;
                    cout << "*-----------------------*" << endl << endl;
                    cout << "Elija el destinatario" << endl << endl;
                    /* aca va la logica de como elegir el destinatario
                     * para poder armar el mensaje a enviar, se arma en base a
                     * la lista que nos trajimos del servidor al conectar el 
                     * programa*/

                     /* La ultima opcion manda mensaje que es para todos los users */

                    // Message* mensaje = new Message(20,"tu","vieja","entanga");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja3");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja5");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("hola", "tuvieja");
                    cliente1->send_message("putoelquelee", "tuvieja20");

                    // delete mensaje;
                    break;
                    }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;
 


            case '3':
                if (conectado) {    
                    cout << "Solicitando mensajes al servidor..." << endl << endl;
                    /* Enviar mensaje especial al server para que 
                    * sepa que le estoy pidiendo los mensajes, el mensaje
                    * especial, debe tener al usuario en cuestion */ 
                    // Message* mensaje = new Message(GETUSERMESSAGES,"","","");
                    // cliente1->send_message(mensaje) ;

                    cliente1->receive_messages();

                    // delete mensaje;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



            case '4':
                if (conectado) {
                    cliente1->disconnect();
                    cout << "Ud. Se ha desconectado del servidor" << endl << endl;
                    conectado = false;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



             case '5':
                if (conectado) {
                    cout << "*-----------------------*" << endl;
                    cout << "!      Lorem Ipsum      !" << endl;
                    cout << "*-----------------------*" << endl << endl;

                    /* Falta implementar el lorem */
                    
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;




            case '6':
                endloop=true;
                cliente1->disconnect();;
                conectado = false;
                delete cliente1;
                break;




            default:
                cin.clear();
                cout << "Opcion no valida." << endl << endl;
                break;
        }
    }while(endloop!=true);

    
    return 0;
}
