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

    EnemySprite(SDL_Renderer *renderer, int window_width, int window_height, EnemyType* enemyType) : Sprite(renderer,window_width,window_height) {
        cambioFrame = 0;
        this->layer = enemyType->getLayer();
        EnemySprite::wActualPosFrame = 0;

        EnemySprite::wFramesCant = enemyType->getCantWidthFrames();

        EnemySprite::frameWidth = enemyType->getImageWidth() / wFramesCant;
        EnemySprite::frameHeight = enemyType->getImageHeight() / enemyType->getCantHeightFrames();


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
