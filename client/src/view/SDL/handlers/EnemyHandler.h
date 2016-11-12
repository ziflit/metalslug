#ifndef METALSLUG_ENEMYBUILDER_H
#define METALSLUG_ENEMYBUILDER_H

#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"
#include "types.h"
#include "../../../utils/Protocol.h"
#include "../spriteClasses/EnemySprite.h"

/**
 * EN UN PRINCIPIO ESTA CLASE ES CAPAZ DE MANEJAR LOS ENEMIGOS DEL TIPO:
 * ENEMY_NORMAL_1
 * ENEMY_NORMAL_2
 * ENEMY_NORMAL_3
 * MAS ADELANTE DEBERIAMOS VER EL TEMA DE LOS ENEMIGOS FINALES.
 */
class EnemyHandler {
private:
    SDL_Renderer *mainRenderer;
    vector<enemyType> enemiesTypes;
    vector<EnemySprite*> enemies;

public:

    EnemyHandler(SDL_Renderer* mainRenderer);

    void newEnemyType(int ancho, int alto, Entity id, char imagePath[40], int cantWidthFrames, int cantHeightFrames);

    SDL_Texture* createTexture(string imageTexturePath);

    bool isEnemyType(Entity id);

    void handle(event newEvent);

    void updateEnemiesSprites();

    enemyType getEnemyType(Entity id);

    EnemySprite* getEnemyToHandle(event newEvent);

    void newLevel();
};


#endif //METALSLUG_ENEMYBUILDER_H
