#include <iostream>
#include "EnemyHandler.h"
EnemyHandler::EnemyHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

SDL_Texture* EnemyHandler::createTexture(string imageTexturePath) {
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());
    if (loadingSurface == NULL) {
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }
    backgroundTexture = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);
    if (backgroundTexture == NULL) cout<<"Error creating background layer: "<<SDL_GetError()<<endl;
    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}

void EnemyHandler::newEnemyType(xmlEnemy enemyConfig) {

    struct enemyType newType;

    SDL_Texture* layer = this->createTexture(enemyConfig.path);
    SDL_QueryTexture(layer, NULL, NULL, &newType.spriteImageWidth, &newType.spriteImageHeight);

    newType.ancho =enemyConfig.ancho;
    newType.alto = enemyConfig.alto;
    newType.id = enemyConfig.id;
    newType.layer = layer;
    newType.cantWidthFrames = enemyConfig.cantWidthFrames;
    newType.cantHeigthFrames = enemyConfig.cantHeightFrames;

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
    if(newEvent.data.postura == MUERTO){
        deleteEnemy(newEvent.data.username);
    } else {
        this->getEnemyToHandle(newEvent)->handle(newEvent);
    }
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
    enemies.clear();
}
void EnemyHandler::deleteEnemy(char *username) {
    auto it = enemies.begin();
    while(it != enemies.end()) {
        if ((*it)->getNumber() == atoi(username)) {
            enemies.erase(it);
        }
    }
}
