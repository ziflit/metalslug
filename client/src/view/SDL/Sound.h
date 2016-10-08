//
// Created by mfprado on 08/10/16.
//

#ifndef SDLBASE_SOUND_H
#define SDLBASE_SOUND_H

#include "SDL2/SDL_mixer.h"


class Sound {
private:
    Mix_Chunk* sound;
public:
    Sound(char* soundPath);
    void playOnce();
    virtual ~Sound();
};


#endif //SDLBASE_SOUND_H
