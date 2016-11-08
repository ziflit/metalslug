//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYSPRITE_H
#define METALSLUG_ENEMYSPRITE_H

#include "Sprite.h"

class EnemySprite : public Sprite{

private:
    int wFramesCant,wActualPosFrame, cambioFrame;


public:

    EnemySprite(SDL_Renderer *renderer,SDL_Texture* layer, int window_width, int window_height) : Sprite(renderer,window_width,window_height) {
        cambioFrame = 0;
    }

    void setUpImage(string imageSpritePath,
                    int wFramesCant, int hFramesCant);


    void handle(struct event nuevoEvento);

    void setNextSpriteFrame();

    void caminandoDerecha();
    void caminandoIzquierda();
    void disparandoCaminandoDerecha();
    void disparandoCaminandoIzquierda();
    void muerto();
};


#endif //METALSLUG_ENEMYSPRITE_H
