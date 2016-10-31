//
// Created by leandro on 30/10/16.
//

#include "PlayerBuilder.h"

Player *PlayerBuilder::createPlayer(int  playerNumber, string user, int windowWidth) {
    auto search = playerCreator.find(playerNumber);
    if (search != playerCreator.end()) {
        auto &creator = search->second;
        return creator(user, windowWidth);
    } else {
        return nullptr;
    }
}
