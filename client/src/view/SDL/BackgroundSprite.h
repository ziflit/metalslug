//
// Created by mfprado on 27/09/16.
//

#ifndef SDLBASE_BACKGROUNDSPRITE_H
#define SDLBASE_BACKGROUNDSPRITE_H

#include "Sprite.h"


class BackgroundSprite : Sprite{
private:
    int spriteImageWidthPanned; //es la posicion horizontal que se va a a ir actualizando

public:
    BackgroundSprite(SDL_Texture *texture, SDL_Renderer *renderer, int window_widht,int window_height) :
    Sprite(texture, renderer) {
        BackgroundSprite::set_position(0,0);
        BackgroundSprite::spriteImageWidthPanned=0;
        BackgroundSprite::frameWidth = window_width;
        BackgroundSprite::frameHeight = window_height;
    }

//_______________________________________________________________________________________________

    void setUpImage(string imageSpritePath);

    void setNextSpriteFrame();

//    void setFramePosition(int x){Sprite::sourceRect.x = x;};

    void actualizarDibujo(){Sprite::actualizarDibujo();}

    void setWidth(int w){ Sprite::setWidth(w);}

    void setHeight(int h){ Sprite::setHeight(h);}

    SDL_Texture* getLayer() const { Sprite::getLayer();}

    void set_position(int x, int y){Sprite::set_position(x,y);}

    int getXPosition(){ Sprite::getXPosition();}

    int getYPosition(){ Sprite::getYPosition();}

//_______________________________________________________________________________________________
};


#endif //SDLBASE_BACKGROUNDSPRITE_H

