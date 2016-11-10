//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYBUILDER_H
#define METALSLUG_ENEMYBUILDER_H

#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"
#include "EnemyType.h"
#include "../../utils/Protocol.h"
#include "EnemySprite.h"

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
    int window_width;
    int window_heigth;
    int enemyToHandler;

public:

    EnemyHandler(SDL_Renderer* mainRenderer, int window_width, int window_height);

    void newEnemyType(int ancho, int alto, Entity id, char imagePath[40], int cantWidthFrames, int cantHeightFrames);

    SDL_Texture* createTexture(SDL_Renderer *renderer, string imageTexturePath);

    bool isEnemyType(Entity id);

    void handle(event nuevoEvento);

    void updateEnemiesSprites();

    void modelStateSet();

    enemyType getEnemyType(Entity id);

    bool notEnemiesCreated();

    EnemySprite* getEnemyToHandle(Entity id);

    EnemySprite *createNewEnemyType(Entity id);

    void createEnemyAndHandle(event nuevoEvento);
};


#endif //METALSLUG_ENEMYBUILDER_H
