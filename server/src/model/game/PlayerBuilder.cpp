
#include "PlayerBuilder.h"

Player *PlayerBuilder::createPlayer(int playerNumber, string user, int windowWidth, int groupId) {
    auto search = playerCreator.find(playerNumber);
    if (search != playerCreator.end()) {
        auto &creator = search->second;
        return creator(user, windowWidth, groupId);
    } else {
        return nullptr;
    }
}
