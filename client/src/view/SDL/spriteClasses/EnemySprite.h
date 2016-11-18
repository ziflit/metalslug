#ifndef METALSLUG_ENEMYSPRITE_H
#define METALSLUG_ENEMYSPRITE_H

#include "Sprite.h"
#include "../handlers/types.h"

class EnemySprite : public Sprite{

private:

    int wFramesCant,wActualPosFrame, cambioFrame, number;

public:

    EnemySprite(SDL_Renderer *renderer, enemyType type, int number) : Sprite(renderer) {
        Sprite::id = type.id;
        this->number = number;
        this->cambioFrame = 0;
        EnemySprite::wActualPosFrame = 0;

        this->layer = type.layer;

        EnemySprite::wFramesCant = type.cantWidthFrames;

        EnemySprite::sourceRect.w = type.spriteImageWidth / wFramesCant;
        EnemySprite::sourceRect.h =type.spriteImageHeight / type.cantHeigthFrames;

        EnemySprite::destRect.w = type.ancho;
        EnemySprite::destRect.h = type.alto;

    }


    void handle(struct event nuevoEvento);

    void setNextSpriteFrame();
    int getNumber() { return number;}
    void caminandoDerecha();
    void caminandoIzquierda();
    void disparandoCaminandoDerecha();
    void disparandoCaminandoIzquierda();
    void muerto();
};


#endif //METALSLUG_ENEMYSPRITE_H
