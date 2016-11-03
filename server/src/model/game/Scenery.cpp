#include "Scenery.h"
#include "../EventHandler.h"
#include "../PlayerEventHandler.h"
#include "PlayerBuilder.h"

Scenery::Scenery(ConfigsXML configs) {
    //TODO: Esto se va a cargar en base al XML para inicializar el escenario, o algo asi
    this->initializeFromXML(configs);


    //TODO: setear la velocidad de avance de cada background, el asociado a los players debe tener igual velocidad que ellos.
    //TODO: definir si del XML tambien se setea la cantidad de jugadores.
    //TODO: el seteo de cada jugador.
}
//______________________________________________________________________________________________________________________
//PROCESAMIENTO DE EVENTOS:

void Scenery::initializeFromXML(ConfigsXML configs) {
    this->windowWidth = configs.getGlobalConf().ancho;
    this->windowHeight = configs.getGlobalConf().alto;
    this->playersSpeed = configs.getSpritesConfig()[0].speed;

    vector<xmlBackground> backgroundConfigs = configs.getBackgroundsConfig();

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
    newPlayer->setSpeed(this->playersSpeed);
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

            background->avanzar();

            /**como cada background tiene asignada su propia velocidad no todos avanzan de igual manera.
             * el asociado a los players debe avanzar exactamente igual que ellos.
             * Es por eso que tiene seteada igual velocidad.
             */
        }
        for (auto player : players) {
            if (player->getPostura() != DESCONECTADO) {
                player->retroceder();
            }
        }

    }
}

vector<struct event> Scenery::obtenerEstadoEscenario() {
    vector<struct event> eventsToReturn;


    for (auto player : players) {
        player->updatePosition();
        eventsToReturn.push_back(player->getState());
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

void Scenery::addElementToScenery(Background *background) {
    backgrounds.push_back(background);
}

Scenery::~Scenery() {
}
