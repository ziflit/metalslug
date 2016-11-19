
#ifndef SERVER_POWERBONUSSTRATEGY_H
#define SERVER_POWERBONUSSTRATEGY_H


#include "BonusStrategy.h"

class PowerBonusStrategy : public BonusStrategy {
private:
    vector<Entity> playerEntities = {MARCO, TARMA, FIO, ERI};

    bool isAlly(GameObject *gameObject, int groupId);

public:
    virtual void execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) override;


};


#endif //SERVER_POWERBONUSSTRATEGY_H
