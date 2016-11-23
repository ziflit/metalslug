#ifndef SDLBASE_SOUND_H
#define SDLBASE_SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_mixer.h"

class Sound {
private:
    Mix_Chunk *sound;
public:
    Sound(std::string soundPath);
    void playOnce();
    virtual ~Sound();

    Mix_Chunk *createSound(char *soundPath);
};


#endif //SDLBASE_SOUND_H
