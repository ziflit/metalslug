/*
 * Scenery.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_SCENERY_H_
#define SRC_MODEL_GAME_SCENERY_H_

#include <vector>
#include <string>
#include <queue>
#include "Player.h"
#include "Background.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Plataforma.h"
#include "../Event.h"
#include "../ConfigsXML.h"
#include "../../utils/Protocol.h"

using namespace std;

class Scenery {
private:
    ConfigsXML* configs;
    vector<struct xmlLvl> lvlsConfig;
    bool nivelEnded;
    vector<Player *> players;
    vector<Enemy *> enemies;
    vector<GameObject *> backgrounds;
    vector<Bullet *> bullets; // las vamos a tener que diferencias para que el colisionador pueda usarlas
    int cantPlayers;
    vector<GameObject *> miscs;  // Se utiliza para plataformas, cajas y elementos bonus

    unsigned int windowWidth, windowHeight, playersSpeed;
    
    void setUpLevel(int selectedLevel);

    // *-* El que llame a player debe chequear si ya se llego al maximo de jugadores permitidos en el nivel
    void addElementToScenery(Player *player);

    void addElementToScenery(Bullet *bullet);

    void addElementToScenery(Enemy *enemy);

    void addElementToScenery(Plataforma *platform);

    // El background que se agrega ya debe tener su Z-index definido, asi solamente se agrega al vector
    void addElementToScenery(Background *background);


public:
    Scenery(ConfigsXML* confs, int selectedLevel);

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

    int setLevelConfigs(Entity* z0, Entity* z1, Entity* z2, Entity* en, Entity* ef, int selectedLevel);
};

#endif /* SRC_MODEL_GAME_SCENERY_H_ */
