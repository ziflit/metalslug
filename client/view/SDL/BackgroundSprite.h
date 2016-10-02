//
// Created by mfprado on 27/09/16.
//

#ifndef SDLBASE_BACKGROUNDSPRITE_H
#define SDLBASE_BACKGROUNDSPRITE_H

#include "Sprite.h"


class BackgroundSprite : Sprite{
private:
    int spriteImageWidthPanned;


public:
    BackgroundSprite(SDL_Texture *texture, SDL_Renderer *renderer) :
    Sprite(texture, renderer) {
        BackgroundSprite::set_position(0,0);
        BackgroundSprite::spriteImageWidthPanned=0;
    }

//_______________________________________________________________________________________________

    void setUpImage(string imageSpritePath);

    void update(){Sprite::update();}

    void setWidth(int w){ Sprite::setWidth(w);}
    void setHeight(int h){ Sprite::setHeight(h);}

    SDL_Texture* getLayer() const { Sprite::getLayer();}

    void set_position(int x, int y){Sprite::set_position(x,y);}
    int getXPosition(){ Sprite::getXPosition();}
    int getYPosition(){ Sprite::getYPosition();}

    void setNextSpriteFrame();

    void increaseFrameTime(){Sprite::increaseFrameTime();}
    void restartFrameTime(){Sprite::restartFrameTime();}
    int getFrameTime(){ Sprite::getFrameTime();}

    void moveRight();
    void moveLeft();

//_______________________________________________________________________________________________

    void handleBackgroundEvents(SDL_Event event);
};


#endif //SDLBASE_BACKGROUNDSPRITE_H

