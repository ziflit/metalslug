/*
 * Scenery.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_SCENERY_H_
#define SRC_MODEL_GAME_SCENERY_H_

using namespace std;

class Scenery {
private:
	vector<Player> playerLists;
	vector<Background> backParallax;


public:
	Scenery();
	virtual ~Scenery();

	void addPlayer(Player player);
	Player getPlayer(string playerName);
	void configureParallaxBackgrounds(Background background);
	unsigned int firstBackgroundPosition(); //




};

#endif /* SRC_MODEL_GAME_SCENERY_H_ */
