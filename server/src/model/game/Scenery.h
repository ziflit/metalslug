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
#include <queue>
#include "../Event.h"
#include "../ConfigsXML.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace std;

class Scenery {
private:
    vector<Player *> players;
    vector<Enemy *> enemies;
    vector<GameObject *> backgrounds;
    vector<Bullet> bullets; // las vamos a tener que diferencias para que el colisionador pueda usarlas
    unsigned int windowWidth, windowHeight, playersSpeed;
    void initializeFromXML(ConfigsXML configs);

    // *-* El que llame a player debe chequear si ya se llego al maximo de jugadores permitidos en el nivel
    void addElementToScenery(Player *player);

    void addElementToScenery(Enemy *enemy);

    // El background que se agrega ya debe tener su Z-index definido, asi solamente se agrega al vector
    void addElementToScenery(Background *background);


public:
    Scenery(ConfigsXML configs);

    virtual ~Scenery();

    void process_key(EventCode keycode, Entity entity);

    vector<struct event> process_keys_queue(queue<struct event> *keys);

    Entity buildPlayer(string user);

    bool jugadorPasoMitadPantallaYEstaAvanzando();

    bool hayJugadorEnBordeIzq();

    vector<Player *> getPosJugadorMasAdelantado();

    void updateBackgroudsState();

    vector<struct event> obtenerEstadoEscenario();

    int findPlayerByUsername(string user);

    vector<GameObject*> getVisibleObjects();
};

#endif /* SRC_MODEL_GAME_SCENERY_H_ */
