#include "Scenery.h"
#include "../EventHandler.h"
#include "../PlayerEventHandler.h"
#include "PlayerBuilder.h"
#include <time.h>

Scenery::Scenery(ConfigsXML *confs, int selectedLevel) {
    this->configs = confs;
    this->setUpLevel(selectedLevel);
    cantPlayers = 0;
}

void Scenery::setUpLevel(int selectedLevel) {
    lvlsConfig = this->configs->getLvlsConfig();
    this->nivelEnded = false;

    this->windowWidth = this->configs->getGlobalConf().ancho;
    this->windowHeight = this->configs->getGlobalConf().alto;
    this->playersSpeed = this->configs->getPlayersConfig()[0].speed;

    vector<xmlBackground> backgroundConfigs = this->configs->getBackgroundsConfig();

    // Esto es para resetear la posicion de los players
    if (selectedLevel > 1) {
        for (auto player: players) {
            player->set_position(0, 0);
        }
    }

    //Seteo los backgrounds correspondientes para el nivel
    Entity back_z0, back_z1, back_z2;
    selectedLevel = setLevelBackgrounds(&back_z0, &back_z1, &back_z2, selectedLevel);

    //Borro los viejos y Seteo de enemigos de forma random, en base a la carga del XML
    if (not enemies.size() == 0) enemies.clear();
    srand(time(NULL));
    for (int i = 0; i < lvlsConfig[selectedLevel].cant_enemies; i++) {
        int randomSpawnInX = rand() % 3000 + 800;
        Enemy *enemy = new Enemy(ENEMY_NORMAL_1, randomSpawnInX, 400);
        enemies.push_back(enemy);
    }

    //Borro los viejos y Seteo los pisos y plataformas, en base a la carga del XML
    if (not miscs.size() == 0) miscs.clear();
    for (auto p : lvlsConfig[selectedLevel].platforms) {
        Plataforma *plataforma = new Plataforma(p.x, p.y, p.ancho, p.alto);
        miscs.push_back(plataforma);
    }

    //Borro los backgrounds que haya y Seteo los 3 backgrounds correspondientes al nivel elegido
    if (not backgrounds.size() == 0) backgrounds.clear();
    for (auto backgroundConfig : backgroundConfigs) {
        if (backgroundConfig.id == back_z0 || backgroundConfig.id == back_z1 || backgroundConfig.id == back_z2) {
            Background *newBackground = new Background(backgroundConfig.id, playersSpeed,
                                                       backgroundConfig.ancho, windowWidth);
            this->backgrounds.push_back(newBackground);
        }
    }
    ((Background *) backgrounds[0])->calculateSpeed(this->configs->getBackgroundsConfig()[1].ancho, playersSpeed);
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
        cantPlayers++;
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
    if (not this->nivelEnded) {
        if ((not hayJugadorEnBordeIzq()) and (jugadorPasoMitadPantallaYEstaAvanzando())) {
            for (auto background : backgrounds) {
                this->nivelEnded = ((Background *) background)->avanzarFrame();
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

            for (auto &enemy : enemies) {
                enemy->retroceder();
            }
        }
    } else {
        this->setUpLevel(2);
    }
}

vector<struct event> Scenery::obtenerEstadoEscenario() {
    removeDeadObjects();

    vector<struct event> eventsToReturn;
    vector<GameObject *> all_objects_in_window = this->getVisibleObjects();

    updatePlayersState(eventsToReturn, all_objects_in_window);
    updateEnemiesState(eventsToReturn, all_objects_in_window);
    updateBulletsState(all_objects_in_window);
    updateBackgroudsState();

    for (auto background : backgrounds) {
        eventsToReturn.push_back(background->getState());
    }

    for (auto &bullet : bullets) {
        eventsToReturn.push_back(bullet->getState());
    }

    eventsToReturn.back().completion = EventCompletion::FINAL_MSG;
    return eventsToReturn;
}

void Scenery::updateBulletsState(vector<GameObject *> &all_objects_in_window) {
    for (auto &bullet : bullets) {
        bullet->avanzar(all_objects_in_window);
    }
}

void
Scenery::updateEnemiesState(vector<event> &eventsToReturn, vector<GameObject *> &all_objects_in_window) {
    for (auto enemy : enemies) {
        enemy->updatePosition(all_objects_in_window);
        eventsToReturn.push_back(enemy->getState());
    }
}

void Scenery::updatePlayersState(vector<event> &eventsToReturn, vector<GameObject *> &all_objects_in_window) {
    for (auto player : players) {
        if (player->getShootingState() and player->haveBullets()) {
            bullets.push_back((Bullet *) player->shoot());
        }
        player->updatePosition(all_objects_in_window);
        eventsToReturn.push_back(player->getState());
    }
}

void Scenery::addElementToScenery(Player *player) {
    players.push_back(player);
}

void Scenery::addElementToScenery(Bullet *bullet) {
    bullets.push_back(bullet);
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

vector<GameObject *> Scenery::getVisibleObjects() {
    //TODO: ESTO NO DEBERIA FILTRAR POR LOS QUE ESTAN EN LA PANTALLA?
    vector<GameObject *> todos;
    for (auto &enemy : enemies) {
        todos.push_back(enemy);
    }
    for (auto &misc : miscs) {
        todos.push_back(misc);
    }

    for (auto &player : players) {
        todos.push_back(player);
    }
    return todos;
}

void Scenery::removeDeadObjects() {
    removeDeadBullets();
    removeDeadPlayers();
    removeDeadEnemies();
}

int Scenery::setLevelBackgrounds(Entity *z0, Entity *z1, Entity *z2, int selectedLevel) {
    switch (selectedLevel) {
        case 1:
            *z0 = BACKGROUND_LVL1_Z0;
            *z1 = BACKGROUND_LVL1_Z1;
            *z2 = BACKGROUND_LVL1_Z2;
            return 0;
            break;
        case 2:
            *z0 = BACKGROUND_LVL2_Z0;
            *z1 = BACKGROUND_LVL2_Z1;
            *z2 = BACKGROUND_LVL2_Z2;
            return 1;
            break;
        case 3:
            *z0 = BACKGROUND_LVL3_Z0;
            *z1 = BACKGROUND_LVL3_Z1;
            *z2 = BACKGROUND_LVL3_Z2;
            return 2;
            break;
    }
}

void Scenery::removeDeadBullets() {
    vector<Bullet *>::iterator it = bullets.begin();
    while (it != bullets.end()) {
        if ((*it)->getEntity() == DEAD) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void Scenery::removeDeadPlayers() {
    vector<Player *>::iterator it = players.begin();
    while (it != players.end()) {
        if ((*it)->getPostura() == MUERTO) {
            it = players.erase(it);
        } else {
            ++it;
        }
    }
}

void Scenery::removeDeadEnemies() {
    vector<Enemy *>::iterator it = enemies.begin();
    while (it != enemies.end()) {
        if ((*it)->getPostura() == MUERTO) {
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}