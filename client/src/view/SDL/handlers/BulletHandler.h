#ifndef METALSLUG_BULLETHANDLER_H
#define METALSLUG_BULLETHANDLER_H


#include <SDL2/SDL_system.h>
#include "../../../utils/Protocol.h"
#include "types.h"
#include "../spriteClasses/BulletSprite.h"

class BulletHandler {
private:
    SDL_Renderer *mainRenderer;
    vector<simpleSpriteType> bulletsTypes;
    vector<struct event> events;
public:
    BulletHandler(SDL_Renderer *mainRenderer);

    void newBulletType(xmlBullet bulletConfig);

    void handle(event newEvent);

    void updateBulletsSprites();

    simpleSpriteType getBulletType(Entity id);

    BulletSprite* createBulletType(Entity id);

    bool isBulletType(Entity id);

    SDL_Texture *createTexture(string imageTexturePath);
};

#endif //METALSLUG_BULLETHANDLER_H