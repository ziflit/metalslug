#include "EnemyFinal1.h"

EnemyFinal1::EnemyFinal1(Scenery* scenery, int number, int spawnX, int spawnY) : Enemy(number, ENEMY_FINAL_1, 400, 0) {
    this->gravity = 0;
    this->enemySeq = 900;
    this->scenery = scenery;
}

EnemyFinal1::~EnemyFinal1() {};

void EnemyFinal1::updatePosition(vector<GameObject*> &game_objects) {
    int randomEnemySpawn = rand() % 300;
    int spawnEnemyX = (rand() % 100) + 400;
    if (randomEnemySpawn == 1) {
        /* Oh por dios */
        scenery->addElementToScenery(new Enemy(enemySeq++, ENEMY_NORMAL_1, spawnEnemyX, 0));
    }
}

void EnemyFinal1::avanzar(vector<GameObject *> gameObjects) {
    return;
}
