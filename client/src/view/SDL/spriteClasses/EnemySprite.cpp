#include "EnemySprite.h"

void EnemySprite::actualizarDibujo() {
    Sprite::actualizarDibujo();
    if(postura !=MURIENDO and postura!=MUERTO) {
        this->healthText->renderize((this->destRect.x + (sourceRect.w/2)), (this->destRect.y + (sourceRect.h + 50) ));
    }
}
void EnemySprite::setNextSpriteFrame() {
    if(cambioFrame == 2){

        if (EnemySprite::wActualPosFrame == (EnemySprite::wFramesCant - 1)) {
            EnemySprite::wActualPosFrame = 0;
        }
        EnemySprite::sourceRect.x = (sourceRect.w * EnemySprite::wActualPosFrame);
        EnemySprite::wActualPosFrame++;

        cambioFrame = 0;
    } else {
        cambioFrame++;
    }
}
void EnemySprite::handle(struct event nuevoEvento) {

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);
    this->healthText->changeText(nuevoEvento.data.health);
    this->postura = nuevoEvento.data.postura;
    switch (postura){

        case CAMINANDO_DERECHA:
            caminandoDerecha();
            break;
        case CAMINANDO_IZQUIERDA :
            caminandoIzquierda();
            break;
        case DISPARANDO_CAMINANDO_DERECHA:
            disparandoCaminandoDerecha();
            break;
        case DISPARANDO_CAMINANDO_IZQUIERDA:
            disparandoCaminandoIzquierda();
            break;
        case MIRANDO_DERECHA_QUIETO:
            mirandoDerechaQuieto();
            break;
        case MIRANDO_IZQUIERDA_QUIETO:
            mirandoIzquierdaQuieto();
            break;
        case MURIENDO:
            mueriendo();
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
    this->sourceRect.y = (sourceRect.h * 1);
    this->setNextSpriteFrame();
}
void EnemySprite::disparandoCaminandoDerecha() {
    this->sourceRect.y = (sourceRect.h * 2);
    this->setNextSpriteFrame();
}
void EnemySprite::disparandoCaminandoIzquierda() {
    this->sourceRect.y = (sourceRect.h * 3);
    this->setNextSpriteFrame();
}
void EnemySprite::mirandoDerechaQuieto() {
    this->sourceRect.y = (sourceRect.h * 4);
    this->setNextSpriteFrame();
}

void EnemySprite::mirandoIzquierdaQuieto() {
    this->sourceRect.y = (sourceRect.h * 5);
    this->setNextSpriteFrame();
}

void EnemySprite::mueriendo() {
    this->sourceRect.y = (sourceRect.h * 6);
}
