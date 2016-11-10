#ifndef METALSLUG_ENEMYTYPE_H
#define METALSLUG_ENEMYTYPE_H

#include "../../utils/Protocol.h"
#include "SDL2/SDL.h"

struct enemyType {

    int ancho;
    int alto;
    Entity id;
    int cantWidthFrames, cantHeigthFrames;
    SDL_Texture* layer;
    int spriteImageWidth;
    int spriteImageHeight;
};

struct bulletType {
    int ancho;
    int alto;
    Entity id;
    SDL_Texture* layer;
};


#endif //METALSLUG_ENEMYTYPE_H
