/*
 * Scenery.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Scenery.h"

Scenery::Scenery(unsigned int width, unsigned int height) {
	//TODO: Esto se va a cargar en base al XML para inicializar el escenario, o algo asi
	windowWidth = 800;
	windowHeight = 600;
}

Scenery::~Scenery() {
}

// La papa de la velocidad del juego esta en esta funcion
vector<struct event> Scenery::obtenerEstadoEscenario() {
	vector<struct event> eventsToReturn;
	for (auto player : players) {
		eventsToReturn.push_back(player.getNewState());
	}
	for (auto background : backgrounds) {
		eventsToReturn.push_back(background.getState());
	}
	return eventsToReturn;
}


void Scenery::process_key(EventCode keycode, Entity entity) {
	for (auto player : players) {
		if (player.getEntity() == entity){
			player.updateState(keycode);
		}
	}
}


vector<struct event> Scenery::process_keys_queue(queue<Event> keys){
	for (unsigned int i = 0 ; i<keys.size() ; i++){
		Event key = keys.front();
		Scenery::process_key( key.getCode(), key.getEntity() );
	}
	return obtenerEstadoEscenario();
}


void Scenery::addElementToScenery(Player player) {
	players.push_back(player);
}

void Scenery::addElementToScenery(Background background) {
	backgrounds.push_back(background);
}
