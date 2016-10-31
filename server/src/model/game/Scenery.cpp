#include "Scenery.h"
#include "../EventHandler.h"
#include "../PlayerEventHandler.h"
#include "PlayerBuilder.h"

Scenery::Scenery(ConfigsXML configs) {
    //TODO: Esto se va a cargar en base al XML para inicializar el escenario, o algo asi
    this->configs = configs;
    windowWidth = configs.getGlobalConf().ancho;
    windowHeight = configs.getGlobalConf().alto;

    this->inizializarBackgrounds();

    //TODO: setear la velocidad de avance de cada background, el asociado a los players debe tener igual velocidad que ellos.
    //TODO: definir si del XML tambien se setea la cantidad de jugadores.
    //TODO: el seteo de cada jugador.
}
//______________________________________________________________________________________________________________________
//PROCESAMIENTO DE EVENTOS:

Entity Scenery::buildPlayer(string user) {
    int position = this->findPlayerByUsername(user);
    if (position != -1) {
        return players[position]->getEntity();
    }

    PlayerBuilder playerBuilder;
    Player *newPlayer = playerBuilder.createPlayer(players.size(), user, windowWidth);
    if (newPlayer != nullptr) {
        this->addElementToScenery(newPlayer);
    } else {
        return NOPLAYER;
    }
    return newPlayer->getEntity();
}

void Scenery::inizializarBackgrounds() {
    Background *background0 = new Background(0, 1, configs.getBackgroundsConfig()[0].ancho);
    float background0Speed = calculateBackgroundSpeed(configs.getBackgroundsConfig()[1].ancho, background0->getLarge(),
                                                      configs.getSpritesConfig()[0].speed);
    background0->setSpeed(background0Speed);
    this->backgrounds.push_back(
            background0);  //esos numeros son el largo de la imagen para que autocalcule la velocidad
    this->backgrounds.push_back(
            new Background(1, configs.getSpritesConfig()[0].speed, configs.getBackgroundsConfig()[1].ancho));

    Background *background2 = new Background(2, configs.getSpritesConfig()[0].speed,
                                             configs.getBackgroundsConfig()[2].ancho);
    // background2->calculateSpeed(configs.getBackgroundsConfig()[1].ancho, configs.getSpritesConfig()[0].speed);
    this->backgrounds.push_back(background2);
}

int Scenery::calculateBackgroundSpeed(int largeMainBackground, int largeBackground, int speedMainBackground) {
    return ((largeBackground - 800) * speedMainBackground) / (largeMainBackground - 800);
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
