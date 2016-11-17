
#ifndef SERVER_BONUSMANAGER_H
#define SERVER_BONUSMANAGER_H


#include <functional>
#include <map>
#include "GameObject.h"
#include "KillAllBonusStrategy.h"
#include "WeaponBonusStrategy.h"
#include "PowerBonusStrategy.h"

class BonusManager {
private:
    static BonusStrategy* getBonusStrategy(Entity entity);
public:
    static bool execute(GameObject *gameObject, vector<GameObject *> &gameObjects, Player *player);
};


#endif //SERVER_BONUSMANAGER_H
