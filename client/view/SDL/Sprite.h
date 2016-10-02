#ifndef SDLBASE_SPRITE_H
#define SDLBASE_SPRITE_H



using namespace std;
#include <iostream>
#include "SDLTools.h"

class Sprite {
protected:
    SDL_Rect sourceRect; //rect donde se dibuja el sprite
    SDL_Rect destRect;   //rect donde se hospeda el sprite anterior, este define la pos y tamanio

    SDL_Texture* layer;
    SDL_Renderer* renderer;

    int spriteImageWidth,spriteImageHeight;

    int frameWidth, frameHeight;

    int frameTime;


public:
    //CONSTRUCTOR
    Sprite(SDL_Texture *layer, SDL_Renderer *renderer);

    void setUpImage(string imageSpritePath);
//_________________________________________________________________________________________________________
    //ACTUALIZACION DEL SPRITE
    void setNextSpriteFrame();
    void update();
//_________________________________________________________________________________________________________
    //TAMANO DEL SPRITE:
    void setWidth(int w){ Sprite::destRect.w = w;}
    void setHeight(int h){ Sprite::destRect.h = h;}
//_________________________________________________________________________________________________________
    //POSICION DEL SPRITE:
    void set_position(int x, int y);
    int getXPosition(){ return Sprite::destRect.x;}
    int getYPosition(){ return Sprite::destRect.y;}
//________________________________________________________________________________________________________

    SDL_Texture* getLayer() const { return layer;}
//_________________________________________________________________________________________________________
    //FRAMETIME
    void increaseFrameTime(){frameTime++;}
    void restartFrameTime(){frameTime = 0;}
    int getFrameTime(){ return frameTime;}

};



#endif //SDLBASE_SPRITE_H
