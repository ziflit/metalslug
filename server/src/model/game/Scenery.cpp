#include "Scenery.h"

Scenery::Scenery(unsigned int width, unsigned int height) {
    //TODO: Esto se va a cargar en base al XML para inicializar el escenario, o algo asi
    windowWidth = width;
    windowHeight = height;

    this->backgrounds.push_back(new Background(0,5,4000));
    this->backgrounds.push_back(new Background(1,10,8192));
    this->backgrounds.push_back(new Background(2,10,8192));
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
    Player* newPlayer;

    if(players.size() == 0){
        newPlayer = new Player(user, MARCO);
        this->addElementToScenery(newPlayer);
    }
    else if(players.size() == 1){
        newPlayer = new Player(user, FIO);
        this->addElementToScenery(newPlayer);
    }
    else if(players.size() == 2){
        newPlayer = new Player(user, TARMA);
        this->addElementToScenery(newPlayer);
    }
    else if(players.size() == 3){
        newPlayer = (new Player(user, ERI));
        this->addElementToScenery(newPlayer);
    }
    else if(players.size() > 3){ return NOPLAYER; }
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
    for (auto player : players) {
        if (player->getEntity() == entity){
                player->updateState(keycode);
        }
    }
}

vector<struct event> Scenery::process_keys_queue(queue<struct event> *keys){
    while (not keys->empty()) {
        struct event key = keys->front();
        process_key( key.data.code, key.data.id );
        keys->pop();
    }
    return obtenerEstadoEscenario();
}


bool Scenery::hayJugadorEnBordeIzq(){
    for (auto player: players){
        if(player->getPostura() != Postura::DESCONECTADO){  //ESTO LO ARRASTRA A TODO AQUE DESCONECTADO
            if(player->getX() <= 10) {
                return true;
            }
        }
    }
    return false;
}

bool Scenery::jugadorPasoMitadPantallaYEstaAvanzando(){

    for (auto player : players) {
        if ((player->getX() >= ((windowWidth/2) - 100)) and (player->getDireccionX() == 1)) {
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

            //TODO QUE ARRASTRE AL GRISADO
            for (auto player : players) {
                player->retroceder();
            }
        }

    }
}
vector<struct event> Scenery::obtenerEstadoEscenario() {
    vector<struct event> eventsToReturn;

    updateBackgroudsState();

    for (auto player : players) {
        player->updatePosition();
        eventsToReturn.push_back(player->getNewState());
    }


    for (auto background : backgrounds) {
        eventsToReturn.push_back(background->getState());
    }

    eventsToReturn.back().completion = EventCompletion::FINAL_MSG;
    return eventsToReturn;
}

void Scenery::addElementToScenery(Player* player) {
	players.push_back(player);
}

void Scenery::addElementToScenery(Background* background) {
	backgrounds.push_back(background);
}

Scenery::~Scenery() {
}
