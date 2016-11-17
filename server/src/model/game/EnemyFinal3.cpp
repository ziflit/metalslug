#include "EnemyFinal3.h"

EnemyFinal3::EnemyFinal3(int number, int spawnX, int spawnY) : Enemy(number, ENEMY_FINAL_3, spawnX, spawnY) {
    this->gravity = 0;
}

EnemyFinal3::~EnemyFinal3() {};

void EnemyFinal3::updatePosition(vector<GameObject*> game_objects) {

}

void EnemyFinal3::avanzar(vector<GameObject *> gameObjects) {
    return;
}
