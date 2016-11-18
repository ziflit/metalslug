
#ifndef SERVER_ENEMY_F1_H
#define SERVER_ENEMY_F1_H

#include "Enemy.h"

class Scenery;

class EnemyFinal1 : public Enemy {
    private:
    int gravity;
    int enemySeq;
    Scenery* scenery;

    public:

    EnemyFinal1(Scenery* scenery, int number, int spawnX, int spawnY);

    virtual ~EnemyFinal1();

    virtual void avanzar(vector<GameObject *> gameObjects) override;

    void updatePosition(vector<GameObject *> &game_objects) override;
};

#endif
