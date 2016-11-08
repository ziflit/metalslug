//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_BACKGROUNDSPRITE_H
#define METALSLUG_BACKGROUNDSPRITE_H

#include "Sprite.h"

class BackgroundSprite : public Sprite{
private:

public:
    BackgroundSprite(SDL_Renderer* renderer, int window_width,int window_height) :
            Sprite(renderer,window_width,window_height) {

        BackgroundSprite::set_position(0,0);
        BackgroundSprite::frameWidth = window_width;
        BackgroundSprite::frameHeight = window_height;

        BackgroundSprite::setWidth(window_width);
        BackgroundSprite::setHeight(window_height);

        BackgroundSprite::sourceRect.w = window_width;
        BackgroundSprite::sourceRect.h = window_height;
    }

    void handle(struct event nuevoEvento);

    void setFramePosition(int x);

    void setNextStartBackFrame();

    void setSourceRectWidth(int w){sourceRect.w = w;}
    void setSourceRectHeight(int h){sourceRect.h = h;}

    int getSpriteImageWidth() { return this->spriteImageWidth; }
    int getSpriteImageHeight() { return this->spriteImageHeight; }
};




#endif //METALSLUG_BACKGROUNDSPRITE_H
