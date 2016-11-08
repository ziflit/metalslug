//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYTYPE_H
#define METALSLUG_ENEMYTYPE_H


#include <SDL2/SDL_system.h>
#include "../../utils/Protocol.h"

class EnemyType {
private:

    int ancho;
    int alto;
    Entity id;
    int cantWidthFrames, cantHeigthFrames;
    SDL_Texture* layer;
    int spriteImageWidth;
    int spriteImageHeight;

public:

    EnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames, SDL_Renderer* mainRenderer);

    SDL_Texture *createTexture(SDL_Renderer *renderer, string imageTexturePath);
};


#endif //METALSLUG_ENEMYTYPE_H
