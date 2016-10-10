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
//        TODO: este seteo se hace a partir del XML
        //DEFAULT SIZE
        PlayerSprite::setHeight(100);
        PlayerSprite::setWidth(100);
        //DEFAULT POSITION
        PlayerSprite::set_position(0,0);  //Camino rocoso de la imagen
    }

//_______________________________________________________________________________________________
    //OVERRIDE FUNCTIONS:

    void setUpImage(string imageSpritePath, int wFramesCant, int hFramesCant);

    void actualizarDibujo(){Sprite::actualizarDibujo();}

    void setWidth(int w){ Sprite::setWidth(w);}
    void setHeight(int h){ Sprite::setHeight(h);}

    SDL_Texture* getLayer() const { Sprite::getLayer();}

    void set_position(int x, int y){Sprite::set_position(x,y);}
    int getXPosition(){ Sprite::getXPosition();}
    int getYPosition(){ Sprite::getYPosition();}

    void setNextSpriteFrame();

    void upArrowPress();
    void rightStep();
    void leftStep();
    void downArrowPress();

//______________________________________________________________________________________________

};



#endif //SDLBASE_PLAYERSPRITE_H
