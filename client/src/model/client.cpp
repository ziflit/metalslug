#include "client.h"

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../utils/Logger.h"
#include <sstream>
#include "ClientHandler.h"

using namespace std;

bool Client::connect_to_server(string ip, int port, string user) {
	struct sockaddr_in server_addr;
	socklen_t server_sock_size;

	/* Abro el socket del cliente */
	socket_number = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_number < 0) {
		LOGGER_WRITE(Logger::ERROR, "Error abriendo el socket.", CLASSNAME)
		cout << "Error abriendo el socket del cliente: " << strerror(errno)
				<< endl;
		return false;
	}
	/* Configuro las direcciones del cliente */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip.data());
	server_sock_size = sizeof(server_addr);

	/* Me conecto al servidor. Devuelve -1 si la conexion falla */
	if (connect(socket_number, (struct sockaddr *) &server_addr,
			server_sock_size) < 0) {
		LOGGER_WRITE(Logger::ERROR, "Error abriendo el socket.", CLASSNAME)
		cout << "Error conectando al servidor: " << strerror(errno) << endl;
		return false;
	}

	/*Envio mje al servidor*/
	cout << send(socket_number, user.data(), 20, 0) << endl;
	char response[MSGSIZE];

	//respuesta de login OK/FAIL
	recv(socket_number, response, MSGSIZE, 0);

	if (((event *) response)->data.code == EventCode::LOGIN_FAIL) {
		LOGGER_WRITE(Logger::ERROR, "Error de autenticacion de usuario.",
				CLASSNAME)
		cout << "No se pudo loguear, intente nuevamente"
				<< endl;
		return false;
	} else {
		strcpy(userName, user.data());

    struct xmlConfig globalConf;
    recv(socket_number, &globalConf, sizeof(struct xmlConfig), 0);

    struct xmlGameMode gameModeConf;
    recv(socket_number, &gameModeConf, sizeof(struct xmlGameMode), 0);


        /* Recepción de configuraciones de sprites de jugadores */
    vector<struct xmlPlayer> playersConfig;
    struct xmlPlayer playerSetup;
    do {
        recv(socket_number, &playerSetup, sizeof(struct xmlPlayer), 0);
		playersConfig.emplace_back(playerSetup);
    } while (playerSetup.completion != EventCompletion::FINAL_MSG);

    /* Recepción de configuraciones de sprites de enemigos */
    vector<struct xmlEnemy> enemiesConfig;
    struct xmlEnemy enemySetup;
    do {
        recv(socket_number, &enemySetup, sizeof(struct xmlEnemy), 0);
        enemiesConfig.emplace_back(enemySetup);
    } while (enemySetup.completion != EventCompletion::FINAL_MSG);

    /* Recepción de configuraciones de backgrounds */
    vector<struct xmlBackground> backgroundsConfig;
    struct xmlBackground backSetup;
    do {
        recv(socket_number, &backSetup, sizeof(struct xmlBackground), 0);
        backgroundsConfig.emplace_back(backSetup);
    } while (backSetup.completion != EventCompletion::FINAL_MSG);

    /* Recepción de configuraciones de bullets */
    vector<struct xmlBullet> bulletsConfig;
    struct xmlBullet bulletSetup;
    do {
        recv(socket_number, &bulletSetup, sizeof(struct xmlBullet), 0);
        bulletsConfig.emplace_back(bulletSetup);
    } while (bulletSetup.completion != EventCompletion::FINAL_MSG);

    /* Recepción de configuraciones de miscelaneas */
    vector<struct xmlMiscelanea> miscelaneasConfig;
    struct xmlMiscelanea miscSetup;
    do {
        recv(socket_number, &miscSetup, sizeof(struct xmlMiscelanea), 0);
        miscelaneasConfig.emplace_back(miscSetup);
    } while (miscSetup.completion != EventCompletion::FINAL_MSG);

    /* Una vez recibidas las configuraciones las aplico en el cliente */
    loadConfigsFromServer(globalConf, gameModeConf,playersConfig, enemiesConfig, backgroundsConfig,
                         bulletsConfig, miscelaneasConfig);

    this->my_character = ((struct event*) response)->data.id;
    return true;

    }

}

void Client::disconnect() {
  send_disconnect_to_server();
  sleep(1);
  this->handler->stop();
	delete this->handler;
	this->set_connection_status(false);
	usersList.clear();
}

void Client::send_disconnect_to_server() {
	struct event disconnectEvent;
  disconnectEvent.data.code = EventCode::CLIENT_DISCONNECT;
  disconnectEvent.completion = EventCompletion::FINAL_MSG;
	this->handler->sendEvent(disconnectEvent);
}

int Client::send_message(struct event eventToSend) {
	this->handler->sendEvent(eventToSend);
}

int Client::receive_messages() {
	char buffer[MSGSIZE];
	int countMessages = 0;
//	MessageUtils messageutils;
	SocketUtils sockutils;
	vector<struct event> small_messages;
	bool is_server_alive;
	do {
		do {
			small_messages.clear();
			is_server_alive = sockutils.readSocket(socket_number, buffer);
			if (not is_server_alive) {
				return -1;
			}
			small_messages.push_back(*(struct event *) buffer);
		} while ((*(struct event *) buffer).completion
				!= EventCompletion::FINAL_MSG and is_server_alive);
		if ((*(struct event *) buffer).data.code == EventCode::MSG_OK) {
			continue;
		} /* Ignoro el heartbeat */
//		Event *message = messageutils.buildMessage(small_messages);
		countMessages++;
//		cout << message->getFrom() << ": " << message->getContent() << endl;
	} while ((*(struct event *) buffer).data.code != EventCode::LAST_MESSAGE);
	LOGGER_WRITE(Logger::INFO,
			"Se han recibido " + to_string(countMessages) + " mensajes.",
			CLASSNAME)
}


int Client::get_socket() {
	return socket_number;
}

void Client::loadConfigsFromServer(struct xmlConfig globalConf,
                                   struct xmlGameMode gameModeConfig,
								   vector<struct xmlPlayer> playersConfig,
                                   vector<struct xmlEnemy> enemiesConfig,
                                   vector<struct xmlBackground> backgroundsConfig,
                                   vector<struct xmlBullet> bulletsConfig,
                                   vector<struct xmlMiscelanea> miscelaneasConfig) {
    configs.setGameModeConfig(gameModeConfig);
    configs.setGlobalConf(globalConf);
	configs.setPlayersConfig(playersConfig);
	configs.setEnemiesConfig(enemiesConfig);
    configs.setBackgroundsConfig(backgroundsConfig);
	configs.setBulletsConfig(bulletsConfig);
    configs.setMiscelaneasConfig(miscelaneasConfig);
}

ClientHandler* Client::start_connection() {
    /* Envío un MSG_OK al servidor para avisarle que puede empezar la conexión.
       Desde este lado se arranca el handler para usar la conexión en paralelo. */
    struct event finished_loading;
    finished_loading.completion = FINAL_MSG;
    finished_loading.data.code = MSG_OK;
    send(socket_number, &finished_loading, sizeof(struct event), 0);

    this->handler = new ClientHandler(socket_number, this, userName);
    this->handler->start();

    return handler;
}
