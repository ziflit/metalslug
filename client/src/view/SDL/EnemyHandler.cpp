//
// Created by mfp on 08/11/16.
//

#include <iostream>
#include "EnemyHandler.h"


EnemyHandler::EnemyHandler(SDL_Window *mainWindow, SDL_Renderer *mainRenderer, int window_width, int window_height) {
    this->mainWindow = mainWindow;
    this->mainRenderer = mainRenderer;
    this->window_width = window_width;
    this->window_heigth = window_height;
    this->enemyToHandled = -1;
}


SDL_Texture* EnemyHandler::createTexture(SDL_Renderer* renderer,string imageTexturePath){
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


void EnemyHandler::newEnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames) {

    SDL_Texture* layer = this->createTexture(mainRenderer,imagePath);
    int spriteImageWidth, spriteImageHeight;
    SDL_QueryTexture(layer, NULL, NULL, &spriteImageWidth, &spriteImageHeight);

    struct enemyType newType;

    newType.ancho = ancho;
    newType.alto = alto;
    newType.id = id;
    newType.layer = layer;
    newType.cantWidthFrames = cantWidthFrames;
    newType.cantHeigthFrames = cantHeightFrames;
    newType.spriteImageWidth = spriteImageWidth;
    newType.spriteImageHeight = spriteImageHeight;

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

void EnemyHandler::handle(event nuevoEvento) {
    if (not this->enemiesCreated()){
            this->createEnemyAndHandle(nuevoEvento);
        }
    else {
        this->getEnemyToHandle(nuevoEvento.data.id)->handle(nuevoEvento);
    }
}

void EnemyHandler::createEnemyAndHandle(event nuevoEvento) {
    EnemySprite* newEnemy = this->createNewEnemyType(nuevoEvento.data.id);
    newEnemy->handle(nuevoEvento);
    this->enemies.push_back(newEnemy);
}

void EnemyHandler::updateEnemiesSprites() {
    this->modelStateSet();

    for(auto enemy : enemies) {
        enemy->actualizarDibujo();
    }
}

void EnemyHandler::modelStateSet() {
    if(enemyToHandled < enemies.size() ){
        //todo: algo esta pasando que el modelo del server no me esta enviando el estado de todos los enemigos.
        //creo que esto es bueno chequearlo mas que nada por coherencia entre server-cliente
        cout<<"NO ESTA SIENDO COHERENTE EL SERVER-CLIENTE"<<endl;
    }
        this->enemyToHandled = 0;
}

enemyType EnemyHandler::getEnemyType(Entity entity) {
    for (auto type : enemiesTypes){
        if(type.id == entity) {
            return type;
        }
    }
    return enemiesTypes[0];
}

bool EnemyHandler::enemiesCreated() {
    return (enemyToHandled == -1);
}

EnemySprite* EnemyHandler::getEnemyToHandle(Entity entity) {

    if(enemies[enemyToHandled]->getId() == entity){ //compruebo que realmente este handleando el enemigo correcto
        this->enemyToHandled += 1;
        return enemies[enemyToHandled];
    }
    //si el enemigo a manejar no se corresponde con la entity del evento se crea un enemigo... esto no deberia pasar nunca.
    EnemySprite* newEnemy = this->createNewEnemyType(entity);
    this->enemies.push_back(newEnemy);
    return newEnemy;

}

EnemySprite *EnemyHandler::createNewEnemyType(Entity entity) {

    enemyType type = this->getEnemyType(entity);
    return (new EnemySprite(mainRenderer, window_width, window_heigth, type));

}



