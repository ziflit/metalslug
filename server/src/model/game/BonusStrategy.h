
#ifndef SERVER_BONUSSTRATEGY_H
#define SERVER_BONUSSTRATEGY_H


#include "GameObject.h"
#include "AnimatedObject.h"
#include "Player.h"

class BonusStrategy {
public:
    virtual void execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player)= 0;
};


#endif //SERVER_BONUSSTRATEGY_H
