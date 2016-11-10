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
    vector<BackgroundSprite*> backgroundsToUpdate;
public:
    BackgroundHandler(SDL_Renderer *mainRenderer);

    void addBackgroundToHandle(BackgroundSprite* newBack);

    void handle(event newEvent);

    BackgroundSprite * getBackground(Entity id);

    void updateBottomBackgroundSprites();

    void updateFrontBackgroundSprite();
};


#endif //METALSLUG_BACKGROUNDHANDLER_H
