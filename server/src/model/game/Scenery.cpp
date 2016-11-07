#include "Scenery.h"
#include "../EventHandler.h"
#include "../PlayerEventHandler.h"
#include "PlayerBuilder.h"

Scenery::Scenery(ConfigsXML configs) {
    this->initializeFromXML(configs);
}
void Scenery::initializeFromXML(ConfigsXML configs) {
    this->nivelEnded = false;

    this->windowWidth = configs.getGlobalConf().ancho;
    this->windowHeight = configs.getGlobalConf().alto;
    this->playersSpeed = configs.getPlayersConfig()[0].speed;

    vector<xmlBackground> backgroundConfigs = configs.getBackgroundsConfig();

    // Probando para ver si funcionan los enemigos
    Enemy *enemy = new Enemy(ENEMY_NORMAL_1, 3500, 400);
    enemies.push_back(enemy);
    Enemy *enemy2 = new Enemy(ENEMY_NORMAL_2, 5200, 400);
    enemies.push_back(enemy2);
    Enemy *enemy3 = new Enemy(ENEMY_NORMAL_3, 1500, 400);
    enemies.push_back(enemy3);
    //------------------------------------------------------

    this->addElementToScenery(new Plataforma(0, 500, configs.getBackgroundsConfig()[0].ancho, 100));

    for (auto backgroundConfig : backgroundConfigs) {
        Background* newBackground = new Background(backgroundConfig.id,playersSpeed,
                                                backgroundConfig.ancho,windowWidth);
        this->backgrounds.push_back(newBackground);
    }
    ((Background*)backgrounds[0])->calculateSpeed(configs.getBackgroundsConfig()[1].ancho, playersSpeed);
}

Entity Scenery::buildPlayer(string user) {
    int position = this->findPlayerByUsername(user);
    if (position != -1) {
        return players[position]->getEntity();
    }

    PlayerBuilder playerBuilder;
    Player *newPlayer = playerBuilder.createPlayer(players.size(), user, windowWidth);
    if (newPlayer != nullptr) {
        newPlayer->setSpeed(this->playersSpeed);
        this->addElementToScenery(newPlayer);

    } else {
        return NOPLAYER;
    }
    return newPlayer->getEntity();
}


int Scenery::findPlayerByUsername(string user) {
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (players[i]->getUsername() == user) {
            return i;
        }
    }
    return -1;
}

void Scenery::process_key(EventCode keycode, Entity entity) {
    PlayerEventHandler playerEventHandler;
    for (auto player : players) {
        if (player->getEntity() == entity) {
            playerEventHandler.handle(keycode, player);
        }
    }
}

vector<struct event> Scenery::process_keys_queue(queue<struct event> *keys) {
    while (not keys->empty()) {
        struct event key = keys->front();
        if (key.data.code == CLIENT_DISCONNECT) {
            cout << "se recibio un evento de Client Disconnect" << endl;
        }
        process_key(key.data.code, key.data.id);
        keys->pop();
    }
    return obtenerEstadoEscenario();
}


bool Scenery::hayJugadorEnBordeIzq() {
    if(this->nivelEnded){
        return true;
    }
    for (auto player: players) {
        if ((player->getPostura() != Postura::DESCONECTADO) and (player->getX() <= 0)) {
            return true;
        }
    }

    return false;
}

bool Scenery::jugadorPasoMitadPantallaYEstaAvanzando() {
    for (auto player : players) {
        if ((player->getPostura() != Postura::DESCONECTADO) and
            ((player->getX() >= ((windowWidth / 2) - 100)) and (player->getDireccionX() == 1))) {
            return true;
        }
    }
    return false;
}

void Scenery::updateBackgroudsState() {
    if ((not hayJugadorEnBordeIzq()) and (jugadorPasoMitadPantallaYEstaAvanzando())) {
        for (auto background : backgrounds) {
            this->nivelEnded = ((Background*)background)->avanzarFrame();
            /**como cada background tiene asignada su propia velocidad no todos avanzan de igual manera.
             * el asociado a los players debe avanzar exactamente igual que ellos.
             * Es por eso que tiene seteada igual velocidad.
             */
        }
        /* Vuelvo atrás todos los elementos que se movieron */
        for (auto player : players) {
            if (player->getPostura() != DESCONECTADO) {
                player->retroceder();
            }
        }
        for (auto &misc : miscs) {
            misc->retroceder(playersSpeed);
        }
    }
}

vector<struct event> Scenery::obtenerEstadoEscenario() {
    vector<struct event> eventsToReturn;

    vector<GameObject*> all_objects_in_window = this->getVisibleObjects();

    for (auto player : players) {
        player->updatePosition(all_objects_in_window);
        eventsToReturn.push_back(player->getState());
    }

    for (auto enemy : enemies) {
        enemy->updatePosition(players[0]->getX()); //Van a seguir siempre al player 1 por ahora
        eventsToReturn.push_back(enemy->getState());
    }

    updateBackgroudsState();

    for (auto background : backgrounds) {
        eventsToReturn.push_back(background->getState());
    }

    eventsToReturn.back().completion = EventCompletion::FINAL_MSG;
    return eventsToReturn;
}

void Scenery::addElementToScenery(Player *player) {
    players.push_back(player);
}

void Scenery::addElementToScenery(Enemy *enemy) {
    enemies.push_back(enemy);
}

void Scenery::addElementToScenery(Plataforma *platform) {
    miscs.push_back(platform);
}

void Scenery::addElementToScenery(Background *background) {
    backgrounds.push_back(background);
}

Scenery::~Scenery() {
    // TODO destruir los putos vectores, tenemos un memory leak
    // del tamaño de una casa?
}

vector<GameObject*> Scenery::getVisibleObjects() {
    vector<GameObject*> todos;
    for (auto &enemy : enemies) {
        todos.push_back(enemy);
    }
    for (auto &misc : miscs) {
        todos.push_back(misc);
    }
    return todos;
}

