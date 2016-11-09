//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYBUILDER_H
#define METALSLUG_ENEMYBUILDER_H

#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"
#include "EnemyType.h"
#include "../../utils/Protocol.h"


class EnemyHandler {
private:
    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
    vector<enemyType> enemiesTypes;
    int window_width;
    int window_heigth;
public:

    EnemyHandler(SDL_Window* mainWindow,SDL_Renderer* mainRenderer, int window_width, int window_height);

    void newEnemyType(int ancho, int alto, Entity id, char imagePath[40], int cantWidthFrames, int cantHeightFrames);

    SDL_Texture* createTexture(SDL_Renderer *renderer, string imageTexturePath);

    bool isEnemyType(Entity id);

    void handle(event nuevoEvento);

    void updateEnemiesSprites();
};


#endif //METALSLUG_ENEMYBUILDER_H
