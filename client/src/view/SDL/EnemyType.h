#ifndef METALSLUG_ENEMYTYPE_H
#define METALSLUG_ENEMYTYPE_H

#include "../../utils/Protocol.h"


struct enemyType {

    int ancho;
    int alto;
    Entity id;
    int cantWidthFrames, cantHeigthFrames;
    SDL_Texture* layer;
    int spriteImageWidth;
    int spriteImageHeight;
};

#endif //METALSLUG_ENEMYTYPE_H
