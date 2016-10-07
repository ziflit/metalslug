//
// Created by mfprado on 27/09/16.
#include "Sprite.h"
#include <SDL2/SDL_events.h>
#include "BackgroundSprite.h"
#ifndef SDLBASE_PLAYERSPRITE_H
#define SDLBASE_PLAYERSPRITE_H

//Los sprites de movimiento de los players deben seguir la forma del ejemplo: sprtes/bicho.png

class PlayerSprite : Sprite{

private:
    int wFramesCant,wActualPosFrame;
    public:
//_______________________________________________________________________________________________
    //Constructor:

    PlayerSprite(SDL_Texture *texture, SDL_Renderer *renderer) : Sprite(texture, renderer) {
        //DEFAULT SIZE
        PlayerSprite::setHeight(150);
        PlayerSprite::setWidth(150);
        //DEFAULT POSITION
        PlayerSprite::set_position(100,window_height-180); 
    }

//_______________________________________________________________________________________________
    //OVERRIDE FUNCTIONS:

    void setUpImage(string imageSpritePath, int wFramesCant, int hFramesCant);

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


//______________________________________________________________________________________________
    void handlePlayerEvents(SDL_Event event,BackgroundSprite* backgroundSprite1,BackgroundSprite*);

    void moveRight();
    void moveLeft();

    void rightStep();
    void leftStep();
    void downArrowPress();
    void upArrowPress();


    void jump(); //con tecla "A" en el juego original
    void duck(); //agacharse

    bool isInHalfWindow();
};



#endif //SDLBASE_PLAYERSPRITE_H
