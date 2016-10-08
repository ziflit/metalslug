/*
 * Scenery.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Scenery.h"

Scenery::Scenery() {
}

Scenery::~Scenery() {
}

void Scenery::obtenerEstadoEscenario() {

}

unsigned int Scenery::firstBackgroundPosition() {

	return 0;
}

void Scenery::process_key(EventCode keycode, string userName) {
	for (auto player : playerList) {
		if (player.getUsername() == userName){
			player.movePlayer(keycode);
		}
	}
}


void Scenery::addElementToScenary(void* elem) {

}

void Scenery::addPlayer(Player player) {
	playerList.push_back(player);
}

void Scenery::addBackground(Background background) {
	backParallax.push_back(background);
}
