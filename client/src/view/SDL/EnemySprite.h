//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYSPRITE_H
#define METALSLUG_ENEMYSPRITE_H

#include "Sprite.h"
#include "EnemyType.h"

class EnemySprite : public Sprite{

private:

    int wFramesCant,wActualPosFrame, cambioFrame;

public:

    EnemySprite(SDL_Renderer *renderer, int window_width, int window_height, enemyType type) : Sprite(renderer, window_width, window_height) {
        this->id = type.id;
        this->cambioFrame = 0;
        EnemySprite::wActualPosFrame = 0;

        this->layer = type.layer;

        EnemySprite::wFramesCant = type.cantWidthFrames;

        EnemySprite::frameWidth = type.spriteImageWidth / wFramesCant;
        EnemySprite::frameHeight = type.spriteImageHeight / type.cantHeigthFrames;


        EnemySprite::sourceRect.w = EnemySprite::frameWidth;
        EnemySprite::sourceRect.h = EnemySprite::frameHeight;

    }


    void handle(struct event nuevoEvento);

    void setNextSpriteFrame();

    void caminandoDerecha();
    void caminandoIzquierda();
    void disparandoCaminandoDerecha();
    void disparandoCaminandoIzquierda();
    void muerto();
};


#endif //METALSLUG_ENEMYSPRITE_H
