#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

void PlayerHandler::addNewPlayer(PlayerSprite *newPlayer) {
    this->playersSprites.push_back(newPlayer);
}

bool PlayerHandler::isPlayerId(Entity id) {
    for (int i = 0 ; i< playersSprites.size() ; i++) {
        if (playersSprites[i]->getId() == id) {
            return true;
        }
    }
    return false;
}

void PlayerHandler::handle(event newEvent) {
    auto it = playersSprites.begin();
    while(it != playersSprites.end()) {
        if ( (*it)->getId() == newEvent.data.id){
            if (newEvent.data.postura == MUERTO) {
                deletePlayer(it);
                return;
            } else {
                (*it)->handle(newEvent);
                return;
            }
        }
        it++;
    }
}

void PlayerHandler::updatePlayersSprites() {
    for (int i = 0 ; i< playersSprites.size() ; i++) {
        playersSprites[i]->actualizarDibujo();
    }
}

PlayerHandler::~PlayerHandler() {
    for (int i = 0 ; i< playersSprites.size() ; i++) {
        delete playersSprites[i];
    }
}

void PlayerHandler::deletePlayer(vector<PlayerSprite *>::iterator it) {
            delete *it;
            playersSprites.erase(it);
}
