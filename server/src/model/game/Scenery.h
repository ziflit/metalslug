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

using namespace std;

class Scenery {
private:
	vector<Player> playerLists;
	vector<Background> backParallax;


public:
	Scenery();
	virtual ~Scenery();

	//TODO: Esta funcion tiene que recibir las distintas teclas que manda cada
	//jugador, para poder actualizar el escenario, hay que ver como va a funcionar
	//lo dejo aca para discutir y ver como implementar
	void actualizarEstadoDelScenario();

	void addPlayer(Player player);
	Player getPlayer(string playerName);
	void configureParallaxBackgrounds(Background background);
	unsigned int firstBackgroundPosition(); //





};

#endif /* SRC_MODEL_GAME_SCENERY_H_ */
