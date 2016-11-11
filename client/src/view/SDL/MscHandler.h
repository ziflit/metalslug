//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_MSCHANDLER_H
#define METALSLUG_MSCHANDLER_H

#include <SDL2/SDL_image.h>
#include "SDL2/SDL.h"
#include "types.h"
#include "MiscelaneaSprite.h"

class MscHandler {
private:
    SDL_Renderer* mainRenderer;
    vector<miscelaneaType> miscelaneasTypes;
    vector<event> events;

public:
    MscHandler(SDL_Renderer* mainRenderer);

    SDL_Texture *createTexture(string imageTexturePath);

    void newMscType(int ancho, int alto, Entity id, char *imagePath);

    void handle(event newEvent);

    void updateMiscelaneaSprites();

    miscelaneaType getMscType(Entity id);

    bool isMscType(Entity id);

    MiscelaneaSprite *createMiscelaneaType(Entity id);
};


#endif //METALSLUG_MSCHANDLER_H
