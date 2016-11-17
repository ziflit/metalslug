#include "EnemyFinal2.h"

EnemyFinal2::EnemyFinal2(int number, int spawnX, int spawnY) : Enemy(number, ENEMY_FINAL_2, spawnX, spawnY) {
    this->gravity = 0;
}

EnemyFinal2::~EnemyFinal2() {};

void EnemyFinal2::updatePosition(vector<GameObject*> game_objects) {

}

void EnemyFinal2::avanzar(vector<GameObject *> gameObjects) {
    return;
}
