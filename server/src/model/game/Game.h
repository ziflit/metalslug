/*
 * Game.h
 *
 *  Created on: Oct 8, 2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_GAME_H_
#define SRC_MODEL_GAME_GAME_H_

#include "Scenery.h"

class Game {
private:
	Scenery* scenery;


public:
	Game();
	virtual ~Game();

	void buildLevel();
};

#endif /* SRC_MODEL_GAME_GAME_H_ */
