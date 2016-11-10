//
// Created by mfp on 08/11/16.
//

#include <iostream>
#include "EnemyHandler.h"


EnemyHandler::EnemyHandler(SDL_Renderer *mainRenderer, int window_width, int window_height) {
    this->mainRenderer = mainRenderer;
    this->window_width = window_width;
    this->window_heigth = window_height;
    this->enemyToHandler = -1;
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

void EnemyHandler::handle(event newEvent) {
    if (this->notEnemiesCreated()){
            return this->createEnemyAndHandle(newEvent);
        }
    else {
        this->getEnemyToHandle(newEvent.data.id)->handle(newEvent);
        this->enemyToHandler += 1;
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
    if(enemyToHandler != (enemies.size()) ){
        //todo: algo esta pasando que el modelo del server no me esta enviando el estado de todos los enemigos.
        //creo que esto es bueno chequearlo mas que nada por coherencia entre server-cliente
        cout<<"NO ESTA SIENDO COHERENTE EL SERVER-CLIENTE"<<endl;
    }
        this->enemyToHandler = 0;
}

enemyType EnemyHandler::getEnemyType(Entity id) {
    for (auto type : enemiesTypes){
        if(type.id == id) {
            return type;
        }
    }
}

bool EnemyHandler::notEnemiesCreated() {
    return (enemyToHandler == -1); //TODO:por ahora es asi pero cuando esta hecho el tema MUERTO este return sera: enemies.size() == 0;
}

EnemySprite* EnemyHandler::getEnemyToHandle(Entity id) {

    if(enemies[enemyToHandler]->getId() == id){ //compruebo que realmente este handleando el enemigo correcto
        return enemies[enemyToHandler];
    }
}

EnemySprite *EnemyHandler::createNewEnemyType(Entity id) {

    enemyType type = this->getEnemyType(id);
    return (new EnemySprite(mainRenderer, window_width, window_heigth, type));

}



