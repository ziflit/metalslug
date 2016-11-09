//
// Created by mfp on 08/11/16.
//

#include <SDL2/SDL_image.h>
#include <iostream>
#include "EnemyType.h"

EnemyType::EnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames, SDL_Renderer* mainRenderer) {
    this->ancho = ancho;
    this->alto = alto;
    this->id = id;
    this->cantWidthFrames = cantWidthFrames;
    this->cantHeigthFrames = cantHeightFrames;
    this->layer = createTexture(mainRenderer, imagePath);
    SDL_QueryTexture(layer, NULL, NULL, &spriteImageWidth, &spriteImageHeight);

}


SDL_Texture* EnemyType::createTexture(SDL_Renderer* renderer,string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());

    if(loadingSurface == NULL){
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

    if(backgroundTexture == NULL){
        cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

    }

    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}

SDL_Texture *EnemyType::getLayer() {
    return layer;
}

int EnemyType::getImageWidth() {
    return spriteImageWidth;
}

int EnemyType::getImageHeight() {
    return spriteImageHeight;
}
