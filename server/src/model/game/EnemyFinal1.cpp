#include "EnemyFinal1.h"

EnemyFinal1::EnemyFinal1(int number, int spawnX, int spawnY) : Enemy(number, ENEMY_FINAL_1, spawnX, spawnY) {
    this->gravity = 0;
}

EnemyFinal1::~EnemyFinal1() {};

void EnemyFinal1::updatePosition(vector<GameObject*> game_objects) {

}

void EnemyFinal1::avanzar(vector<GameObject *> gameObjects) {
    return;
}
