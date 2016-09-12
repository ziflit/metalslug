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
#include "Utils/loremIpsum.h"

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

    cout << "\033[2J\033[1;1H"; /* clear screen */
    do{
        cout << "*-----------------------*" << endl;
        cout << "! Bienvenido al cliente !" << endl;
        cout << "*-----------------------*" << endl << endl;
        cout << "\t1 .- Conectar al servidor" << endl;
        if (conectado == true){
            cout << "\t2 .- Enviar Mensaje" << endl;
            cout << "\t3 .- Chequear mensajes" << endl;
            cout << "\t4 .- Desconectar" << endl;
            cout << "\t5 .- Lorem Ipsum" << endl;
        }
        cout << "\t6 .- Salir" << endl << endl;
        cout << "Elije una opcion: ";
 
        cin >> keypressed;
 
        switch(keypressed)
        {

            case '1':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (!conectado) {
                cout << "Estableciendo la conexion con el servidor..." << endl << endl;
                    if (cliente1->connect_to_server(ip, port) ==  1 ){
                        cliente1->store_users_list();
                        conectado = true;
                    } else {
                        break;
                    }
                   
                }
                cout << " Ud. ya se encuentra conectado al servidor " << endl << endl;
                break;
 


            case '2':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    int userSelected;
                    string contentMsg;

                    cout << "*-----------------------*" << endl;
                    cout << "!    Envio de mensajes   !" << endl;
                    cout << "*-----------------------*" << endl << endl;
                    cliente1->show_users_list();  /* implementar esto */

                    cout << "Elija el destinatario:" << endl << endl;
                    cin >> userSelected;

                    cout << "Escriba el mensaje a enviar:" << endl << endl;
                    // cin >> contentMsg;
                    cin.ignore();
                    getline(cin,contentMsg);

                    cliente1->send_message(userSelected, contentMsg);

                    break;
                    }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;
 


            case '3':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {    
                    cout << "Solicitando mensajes al servidor..." << endl << endl;
                    /* Enviar mensaje especial al server para que 
                    * sepa que le estoy pidiendo los mensajes, el mensaje
                    * especial, debe tener al usuario en cuestion */ 
                    // Message* mensaje = new Message(GETUSERMESSAGES,"","","");
                    // cliente1->send_message(mensaje) ;
                    cliente1->ask_for_messages(); /* implementar esto */

                    cliente1->receive_messages();

                    // delete mensaje;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



            case '4':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    cliente1->disconnect();
                    cout << "Ud. Se ha desconectado del servidor" << endl << endl;
                    conectado = false;
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



             case '5':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                if (conectado) {
                    long max_sends, frequency;
                    cout << "*-----------------------*" << endl;
                    cout << "!      Lorem Ipsum      !" << endl;
                    cout << "*-----------------------*" << endl << endl;

                    cout << "Ingrese la frecuencia deseada:" << endl;
                    cin >> frequency;

                    cout << "Ingrese la cantidad de mensajes a enviar:" << endl;
                    cin >> max_sends;

                    char* path = "src/Utils/arch.txt";
                    LoremIpsum* lorem = new LoremIpsum(frequency,max_sends,path,cliente1);
                    lorem->iniciar();
                    
                    break;
                }
                cout << "Por favor, primero conectese al servidor" << endl << endl;
                break;



            case '6':
                cout << "\033[2J\033[1;1H"; /* clear screen */
                endloop=true;
                cliente1->disconnect();
                conectado = false;
                break;



            default:
                cout << "\033[2J\033[1;1H"; /* clear screen */
                cout << "Opcion no valida." << endl << endl;
                break;
        }
    }while(endloop!=true);


    delete cliente1;
    return 0;
}
