#ifndef METALSLUG_ENEMYSPRITE_H
#define METALSLUG_ENEMYSPRITE_H

#include "Sprite.h"
#include "../handlers/types.h"
#include "../sound-ttf/TextBox.h"

class EnemySprite : public Sprite{
private:
    int wFramesCant,wActualPosFrame, cambioFrame, number;
    TextBox* healthText;
    Postura postura;
public:
    EnemySprite(SDL_Renderer *renderer, enemyType type, int number) : Sprite(renderer) {
        Sprite::id = type.id;
        this->number = number;
        this->cambioFrame = 0;
        EnemySprite::wActualPosFrame = 0;
        healthText = new TextBox(100, this->renderer, {255,0,0,1},12);
        this->layer = type.layer;
        EnemySprite::wFramesCant = type.cantWidthFrames;
        EnemySprite::sourceRect.w = type.spriteImageWidth / wFramesCant;
        EnemySprite::sourceRect.h =type.spriteImageHeight / type.cantHeigthFrames;
        EnemySprite::destRect.w = type.ancho;
        EnemySprite::destRect.h = type.alto;
    }
    void handle(struct event nuevoEvento);
    void actualizarDibujo();
    void setNextSpriteFrame();
    int getNumber() { return number;}
    void caminandoDerecha();
    void caminandoIzquierda();
    void disparandoCaminandoDerecha();
    void disparandoCaminandoIzquierda();
    void mueriendo();
};
#endif //METALSLUG_ENEMYSPRITE_H