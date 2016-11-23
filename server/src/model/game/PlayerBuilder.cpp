
#include "PlayerBuilder.h"

Player *PlayerBuilder::createPlayer(int playerNumber, string user, int windowWidth) {
    auto search = playerCreator.find(playerNumber);
    if (search != playerCreator.end()) {
        auto &creator = search->second;
        Player* player = creator(user, windowWidth, getGroupId(playerNumber));
        player->setHealth(getHealth());
        return player;
    } else {
        return nullptr;
    }
}

void PlayerBuilder::setGameMode(xmlGameMode mode) {
    this->mode = mode;
}

int PlayerBuilder::getGroupId(int playerNumber) {
    switch (this->mode.mode) {
        case INDIVIDUAL:
            return playerNumber;
        case COLABORATIVO:
            return 0;
        case GRUPAL:
            return (playerNumber%2);
    }
}

int PlayerBuilder::getHealth() {
    if (mode.testMode){
        return 999999;
    }
    return 100;
}

