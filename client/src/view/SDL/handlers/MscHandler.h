//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_MSCHANDLER_H
#define METALSLUG_MSCHANDLER_H

#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"
#include "types.h"
#include "../spriteClasses/MiscelaneaSprite.h"

class MscHandler {
private:
    SDL_Renderer* mainRenderer;
    vector<simpleSpriteType> miscelaneasTypes;
    vector<event> events;

public:
    MscHandler(SDL_Renderer* mainRenderer);

    SDL_Texture *createTexture(string imageTexturePath);

    void newMscType(xmlMiscelanea ancho);

    void handle(event newEvent);

    void updateMiscelaneaSprites();

    simpleSpriteType getMscType(Entity id);

    bool isMscType(Entity id);

    MiscelaneaSprite *createMiscelaneaType(Entity id);
};


#endif //METALSLUG_MSCHANDLER_H
