//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_BACKGROUNDHANDLER_H
#define METALSLUG_BACKGROUNDHANDLER_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_system.h>
#include "../spriteClasses/BackgroundSprite.h"

class BackgroundHandler {
private:
    vector<BackgroundSprite*> backgrounds;
    int level;
public:
    BackgroundHandler();

    void addBackgroundToHandle(BackgroundSprite* newBack);

    bool handle(event newEvent);

    BackgroundSprite * getBackground(Entity id);

    void updateBottomBackgroundSprites();

    void updateFrontBackgroundSprite();

    bool setLevel(Entity id);

    BackgroundSprite *getBack0ToUpdate();

    BackgroundSprite *getBack1ToUpdate();

    BackgroundSprite *getBack2ToUpdate();

    bool isBackgroundType(Entity id);
};


#endif //METALSLUG_BACKGROUNDHANDLER_H
