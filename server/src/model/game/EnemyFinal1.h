
#ifndef SERVER_ENEMY_F1_H
#define SERVER_ENEMY_F1_H

#include "Enemy.h"

class EnemyFinal1 : public Enemy {
    private:
    int gravity;

    public:

    EnemyFinal1(int number, int spawnX, int spawnY);

    virtual ~EnemyFinal1();

    virtual event getState() override;

    virtual void avanzar(vector<GameObject *> gameObjects) override;
};

#endif
