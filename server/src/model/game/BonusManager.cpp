

#include "BonusManager.h"

bool BonusManager::execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) {
    BonusStrategy *bonusStrategy = getBonusStrategy(bonus->getEntity());

    if (bonusStrategy != nullptr) {
        bonusStrategy->execute(bonus, gameObjects, player);
        bonus->setEntity(DEAD);
        return true;
    }
    return false;
}

BonusStrategy *BonusManager::getBonusStrategy(Entity entity) {
    if (entity == MSC_BONUS_KILLALL) {
        return new KillAllBonusStrategy();
    } else if (entity == MSC_WEAPON_BOX_HEAVY || entity == MSC_WEAPON_BOX_ROCKET ||
               entity == MSC_WEAPON_BOX_SHOT || entity == MSC_WEAPON_BOX_CHASER) {
        return new WeaponBonusStrategy();
    } else if (entity == MSC_POWER_BONUS) {
        return new PowerBonusStrategy();
    }
    return nullptr;

}
