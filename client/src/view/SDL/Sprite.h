//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_SPRITE_H
#define METALSLUG_SPRITE_H


using namespace std;
#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "../../utils/Protocol.h"

class Sprite {
protected:
    SDL_Rect sourceRect; //rect donde se dibuja el sprite
    SDL_Rect destRect;  //rect donde se hospeda el sprite anterior, este define la pos y tamanio

    SDL_Texture* layer;
    SDL_Renderer* renderer;

    int spriteImageWidth,spriteImageHeight;

    int frameWidth, frameHeight, window_height, window_width;

    Entity id;

public:

    Sprite(SDL_Renderer *renderer, int window_width, int window_height);
    SDL_Texture* loadTexture(SDL_Renderer* renderer,string imageTexturePath);

    virtual void setUpImage(string imageSpritePath);

    virtual void handle(struct event nuevoEvento)=0;

    virtual void actualizarDibujo();

    void setId(Entity id){ this->id = id;}
    Entity getId(){ return id;}

    virtual void setWidth(int w){ Sprite::destRect.w = w;}
    virtual void setHeight(int h){ Sprite::destRect.h = h;}

    virtual void set_position(int x, int y);


};

#endif //METALSLUG_SPRITE_H
