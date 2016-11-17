#include "BulletHandler.h"

BulletHandler::BulletHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

SDL_Texture* BulletHandler::createTexture(string imageTexturePath){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());
    if (loadingSurface == NULL) {
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }
    backgroundTexture = SDL_CreateTextureFromSurface(this->mainRenderer, loadingSurface);
    if (backgroundTexture == NULL) cout<<"Error creating background layer: "<<SDL_GetError()<<endl;
    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}



void BulletHandler::newBulletType(xmlBullet bulletConfig) {
    simpleObjectType newType;

    SDL_Texture* layer = this->createTexture(bulletConfig.path);
    SDL_QueryTexture(layer, NULL, NULL, &newType.frameWidth, &newType.frameHeigth);

    newType.ancho = bulletConfig.ancho;
    newType.alto = bulletConfig.alto;
    newType.id = bulletConfig.id;
    newType.layer = layer;
    this->bulletsTypes.push_back(newType);
}

simpleObjectType BulletHandler::getBulletType(Entity id) {
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
        bullet->handle(event);
        bullet->actualizarDibujo();
    }
    events.clear();
}