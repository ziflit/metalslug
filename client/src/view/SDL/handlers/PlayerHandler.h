//
// Created by mfp on 19/11/16.
//

#ifndef METALSLUG_PLAYERHANDLER_H
#define METALSLUG_PLAYERHANDLER_H


#include <SDL2/SDL_system.h>
#include "../spriteClasses/PlayerSprite.h"

class PlayerHandler {
private:
    vector<PlayerSprite*> playersSprites;
public:
    PlayerHandler(SDL_Renderer *mainRenderer);
};


#endif //METALSLUG_PLAYERHANDLER_H
