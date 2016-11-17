
#include "KillAllBonusStrategy.h"
#include "Enemy.h"
#include <algorithm>

void KillAllBonusStrategy::execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) {
    cout << "ejecutando bonus matar a todos" << endl;
    for (auto object : gameObjects) {
        if (isEnemy(object, player->getShootsTo())) {
            Enemy *enemy = (Enemy *) object;
            enemy->setHealth(0);
            enemy->setPostura(MUERTO);
        }
    }
}

bool KillAllBonusStrategy::isEnemy(GameObject *gameObject, vector<Entity> enemies) {
    vector<Entity>::iterator it = std::find(enemies.begin(), enemies.end(), gameObject->getEntity());
    return it != enemies.end() && (*it) != MSC_PLATFORM;
}
