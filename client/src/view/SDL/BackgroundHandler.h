//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_BACKGROUNDHANDLER_H
#define METALSLUG_BACKGROUNDHANDLER_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_system.h>
#include "BackgroundSprite.h"

class BackgroundHandler {
private:
    SDL_Renderer *mainRenderer;
    vector<BackgroundSprite*> backgrounds;
    int level;
public:
    BackgroundHandler(SDL_Renderer *mainRenderer);

    void addBackgroundToHandle(BackgroundSprite* newBack);

    void handle(event newEvent);

    BackgroundSprite * getBackground(Entity id);

    void updateBottomBackgroundSprites();

    void updateFrontBackgroundSprite();

    void setLevel(Entity id);

    BackgroundSprite *getBack0ToUpdate();

    BackgroundSprite *getBack1ToUpdate();

    BackgroundSprite *getBack2ToUpdate();
};


#endif //METALSLUG_BACKGROUNDHANDLER_H
