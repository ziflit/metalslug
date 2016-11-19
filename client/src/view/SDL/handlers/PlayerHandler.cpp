#include "PlayerHandler.h"

PlayerHandler::PlayerHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

void PlayerHandler::addNewPlayer(PlayerSprite *newPlayer) {
    this->playersSprites.push_back(newPlayer);
}

bool PlayerHandler::isPlayerId(Entity id) {
    return ((id == MARCO) || (id == TARMA) || (id == FIO) || (id == ERI));
}

void PlayerHandler::handle(event newEvent) {
    for (auto player : playersSprites) {
        if ( player->getId() == newEvent.data.id ){
            player->handle(newEvent);
            return;
        }
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
