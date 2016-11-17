
#ifndef SERVER_ENEMY_F3_H
#define SERVER_ENEMY_F3_H

#include "Enemy.h"

class EnemyFinal3 : public Enemy {
    private:
    int gravity;

    public:

    EnemyFinal3(int number, int spawnX, int spawnY);

    virtual ~EnemyFinal3();

    virtual event getState() override;

    virtual void avanzar(vector<GameObject *> gameObjects) override;
};

#endif
