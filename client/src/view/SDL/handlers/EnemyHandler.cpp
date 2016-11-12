#include <iostream>
#include "EnemyHandler.h"


EnemyHandler::EnemyHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

SDL_Texture* EnemyHandler::createTexture(string imageTexturePath){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());
    if(loadingSurface == NULL){
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }
    backgroundTexture = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);
    if(backgroundTexture == NULL){
        cout<<"Error creating background layer: "<<SDL_GetError()<<endl;
    }
    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}

void EnemyHandler::newEnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames) {

    struct enemyType newType;

    SDL_Texture* layer = this->createTexture(imagePath);
    SDL_QueryTexture(layer, NULL, NULL, &newType.spriteImageWidth, &newType.spriteImageHeight);


    newType.ancho = ancho;
    newType.alto = alto;
    newType.id = id;
    newType.layer = layer;
    newType.cantWidthFrames = cantWidthFrames;
    newType.cantHeigthFrames = cantHeightFrames;

    this->enemiesTypes.push_back(newType);
}

bool EnemyHandler::isEnemyType(Entity id) {
    for(auto type : enemiesTypes){
        if(type.id == id) {
            return true;
        }
    }
    return false;
}

void EnemyHandler::handle(event newEvent) {
    this->getEnemyToHandle(newEvent)->handle(newEvent);
}

void EnemyHandler::updateEnemiesSprites() {
    for(auto enemy : enemies) enemy->actualizarDibujo();
}

enemyType EnemyHandler::getEnemyType(Entity id) {
    for (auto type : enemiesTypes){
        if(type.id == id) {
            return type;
        }
    }
}

EnemySprite* EnemyHandler::getEnemyToHandle(event newEvent) {
    int num = atoi(newEvent.data.username);
    for (auto enemy : enemies) {
        if (enemy->getNumber() == num) {
            return enemy;
        }
    }
    EnemySprite* newEnemy = new EnemySprite(mainRenderer, getEnemyType(newEvent.data.id), num);
    enemies.push_back(newEnemy);
    return newEnemy;
}

void EnemyHandler::newLevel() {
    this->enemies.clear();
}




