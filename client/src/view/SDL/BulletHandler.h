//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_BULLETHANDLER_H
#define METALSLUG_BULLETHANDLER_H


#include <SDL2/SDL_system.h>
#include "../../utils/Protocol.h"
#include "types.h"
#include "BulletSprite.h"

class BulletHandler {
private:
    SDL_Renderer *mainRenderer;
    vector<bulletType> bulletsTypes;
    vector<struct event> events;
public:
    BulletHandler(SDL_Renderer *mainRenderer);

    void newBulletType(int ancho, int alto, Entity id, char imagePath[40]);

    void handle(event newEvent);

    void updateBulletsSprites();

    bulletType getBulletType(Entity id);

    BulletSprite* createBulletType(Entity id);

    bool isBulletType(Entity id);

    SDL_Texture *createTexture(SDL_Renderer *renderer, string imageTexturePath);
};


#endif //METALSLUG_BULLETHANDLER_H
