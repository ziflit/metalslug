#include "Scenery.h"

Scenery::Scenery(unsigned int width, unsigned int height) {
	//TODO: Esto se va a cargar en base al XML para inicializar el escenario, o algo asi
    windowWidth = width;
	windowHeight = height;
    //TODO: setear la velocidad de avance de cada background, el asociado a los players debe tener igual velocidad que ellos.
    //TODO: definir si del XML tambien se setea la cantidad de jugadores.
    //TODO: el seteo de cada jugador.
}

//______________________________________________________________________________________________________________________
//PROCESAMIENTO DE EVENTOS:

void Scenery::process_key(EventCode keycode, Entity entity) {
	for (auto player : players) {
		if (player->getEntity() == entity){
			player->updateState(keycode);
		}
    }
}

vector<struct event> Scenery::process_keys_queue(queue<Event> keys){
    for (unsigned int i = 0 ; i<keys.size() ; i++){
        Event key = keys.front();
        process_key( key.getCode(), key.getEntity() );
    }
    return obtenerEstadoEscenario();
}

bool Scenery::todosJugadoresAvanzando(){
    for(auto player : players){
        if(player->getSpeed()<1){ //quieto (speed = 0) o retrocediendo (speed<0)
            return false;
        }
    }
    return true;
}

bool Scenery::hayJugadorEnBordeIzq(){
    for (auto player: players){
        if(player->getX() == 0) {
                return true;
        }
    }
    return false;
}

bool Scenery::jugadorPasoMitadPantalla(){
    for (auto player : players) {
        if (player->getX() > (windowWidth/2)) {
            return true;
        }
    }
    return false;
}

void Scenery::updateBackgroudsState(){

     /* Si un jugador esta en la mitad de pantalla y hay otro en posicion = 0:
     *  entonces se le habilita al jugador a moverse hasta el final de la pantalla y el background no debe avanzar.
     *  Si hay un jugador  retrocediendo o quieto no debe avanzar el background.
     *  Conclusion:
     *  El background avanza unicamente cuando todos estan avanzando, no hay ningun jugador en pos = 0,
     *  y alguno paso la mitad de pantalla
     *  Post el avance del background se debe restar a todos los jugadores una posicion
     */

    if( (todosJugadoresAvanzando()) and (not hayJugadorEnBordeIzq()) and (jugadorPasoMitadPantalla()) ){
        for(auto background : backgrounds){

            background->avanzar();
            //como cada background tiene asignada su propia velocidad no todos avanzan de igual manera.
            //el asociado a los players debe avanzar exactamente igual que ellos.
        }
        for(auto player : players){
            player->retroceder();
        }
    }

}

vector<struct event> Scenery::obtenerEstadoEscenario() {
    vector<struct event> eventsToReturn;
    for (auto player : players) {
        player->updatePosition();
        eventsToReturn.push_back(player->getNewState());
    }

    updateBackgroundsState();

    for (auto background : backgrounds) {
        eventsToReturn.push_back(background->getState());
    }
    return eventsToReturn;
}
//______________________________________________________________________________________________________________________

void Scenery::addElementToScenery(Player* player) {
	players.push_back(player);
}

void Scenery::addElementToScenery(Background* background) {
	backgrounds.push_back(background);
}
//______________________________________________________________________________________________________________________

Scenery::~Scenery() {
}
