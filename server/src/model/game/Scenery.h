/*
 * Scenery.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_SCENERY_H_
#define SRC_MODEL_GAME_SCENERY_H_

#include "Player.h"
#include "Background.h"
#include <vector>
#include <string>
#include "../../utils/Protocol.h"

using namespace std;

class Scenery {
private:
	vector<Player> playerList;
	vector<Background> backParallax;


public:
	Scenery();
	virtual ~Scenery();

	// Funciones para la interaccion con el server, tanto como para recibir las teclas de cada jugador,
	// como para devolver los cambios que generaron dichas teclas.

	//TODO: Esta funcion tiene que recibir las distintas teclas que manda cada
	//jugador, para poder actualizar el escenario, hay que ver como va a funcionar
	//lo dejo aca para discutir y ver como implementar
	void process_key(EventCode keycode, string username);

	void obtenerEstadoEscenario();

	unsigned int firstBackgroundPosition(); //

	// Funciones para agregar objetos al escenario, la idea es que el general recibe cualquier objeto y
	// usa las demas funciones segun sea el caso
	void addElementToScenary(void* elem);

	// *-* El que llame a player debe chequear si ya se llego al maximo de jugadores permitidos en el nivel
	void addPlayer(Player player);

	// El background que se agrega ya debe tener su Z-index definido, asi solamente se agrega al vector
	void addBackground(Background background);




};

#endif /* SRC_MODEL_GAME_SCENERY_H_ */
