//
// Created by mfp on 10/11/16.
//

#include "BulletHandler.h"

BulletHandler::BulletHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

SDL_Texture* BulletHandler::createTexture(SDL_Renderer* renderer,string imageTexturePath){
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



void BulletHandler::newBulletType(int ancho, int alto, Entity id, char *imagePath) {
    bulletType newType;
    newType.ancho = ancho;
    newType.alto = alto;
    newType.id = id;
    newType.layer = this->createTexture(mainRenderer,imagePath);
    this->bulletsTypes.push_back(newType);
}

bulletType BulletHandler::getBulletType(Entity id) {
    for (auto type : bulletsTypes) {
        if (id == type.id) {
            return type;
        }
    }
}

BulletSprite* BulletHandler::createBulletType(Entity id) {
    return (new BulletSprite(mainRenderer, getBulletType(id)));
}

bool BulletHandler::isBulletType(Entity id) {
    for (auto type : bulletsTypes) {
        if (id == type.id) {
            return true;
        }
    }
    return false;
}

void BulletHandler::handle(event newEvent) {
    this->events.push_back(newEvent);
}

void BulletHandler::updateBulletsSprites() {
    for (auto event : events ) {
        BulletSprite* bullet = createBulletType(event.data.id);
        bullet->set_position(event.data.x, event.data.y);
        bullet->actualizarDibujo();
    }
    events.clear();
}