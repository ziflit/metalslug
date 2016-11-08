//
// Created by mfp on 08/11/16.
//

#include "EnemySprite.h"

void EnemySprite::setUpImage(string imageColorPath, int wFramesCant, int hFramesCant) {

    Sprite::setUpImage(imageColorPath);

    EnemySprite::wActualPosFrame = 0;

    EnemySprite::wFramesCant = wFramesCant;

    EnemySprite::frameWidth = spriteImageWidth / wFramesCant;
    EnemySprite::frameHeight = spriteImageHeight / hFramesCant;


    EnemySprite::sourceRect.w = EnemySprite::frameWidth;
    EnemySprite::sourceRect.h = EnemySprite::frameHeight;
}

void EnemySprite::setNextSpriteFrame() {
    if(cambioFrame == 2){

        if (EnemySprite::wActualPosFrame == (EnemySprite::wFramesCant - 1)) {
            EnemySprite::wActualPosFrame = 0;
        }
        EnemySprite::sourceRect.x = (EnemySprite::frameWidth * EnemySprite::wActualPosFrame);
        EnemySprite::wActualPosFrame++;

        cambioFrame = 0;
    } else {
        cambioFrame++;
    }

}

void EnemySprite::handle(struct event nuevoEvento) {

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);

    switch (nuevoEvento.data.postura){

        case Postura::CAMINANDO_DERECHA:
            caminandoDerecha();
            break;
        case Postura::CAMINANDO_IZQUIERDA :
            caminandoIzquierda();
            break;
        case Postura::DISPARANDO_CAMINANDO_DERECHA:
            disparandoCaminandoDerecha();
            break;
        case Postura::DISPARANDO_CAMINANDO_IZQUIERDA:
            disparandoCaminandoIzquierda();
            break;
        case Postura::MUERTO:
            muerto();
            break;
        default:
            break;
    }
}

void EnemySprite::caminandoDerecha() {
    this->sourceRect.y = 0;
    this->setNextSpriteFrame();
}
void EnemySprite::caminandoIzquierda() {
    this->sourceRect.y = (frameHeight * 1);
    this->setNextSpriteFrame();
}
void EnemySprite::disparandoCaminandoDerecha() {
    this->sourceRect.y = (frameHeight * 2);
    this->setNextSpriteFrame();
}
void EnemySprite::disparandoCaminandoIzquierda() {
    this->sourceRect.y = (frameHeight * 3);
    this->setNextSpriteFrame();
}
void EnemySprite::muerto() {
    this->sourceRect.y = (frameHeight * 4);
}
