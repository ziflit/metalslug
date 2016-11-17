#ifndef SERVER_KILLALLBONUSSTRATEGY_H
#define SERVER_KILLALLBONUSSTRATEGY_H


#include "BonusStrategy.h"

class KillAllBonusStrategy : public BonusStrategy {
private:
    bool isEnemy(GameObject *gameObjects, vector<Entity> enemies);

protected:
    virtual void execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) override;


};


#endif //SERVER_KILLALLBONUSSTRATEGY_H
