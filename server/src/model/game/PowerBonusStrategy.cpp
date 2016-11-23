
#include "PowerBonusStrategy.h"
#include <algorithm>

void PowerBonusStrategy::execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) {
    cout << "ejecutando bonus power" << endl;
    for (auto object : gameObjects) {
        if (isAlly(object, player->getGroupId())) {
            Player *playerObj = (Player *) object;
            if (playerObj->getHealth() < 100) {
                playerObj->setHealth(PLAYER_HEALTH);
            }
        }
        if (player->getHealth() < 100) {
            player->setHealth(PLAYER_HEALTH);
        }
    }
}

bool PowerBonusStrategy::isAlly(GameObject *gameObject, int groupId) {
    vector<Entity>::iterator it = std::find(playerEntities.begin(), playerEntities.end(), gameObject->getEntity());
    return (it != playerEntities.end() && ((Player *) gameObject)->getGroupId() != groupId);
}
