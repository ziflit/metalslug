#ifndef SDLBASE_SOUND_H
#define SDLBASE_SOUND_H

#include "SDL2/SDL_mixer.h"
#include <string>

class Sound {
private:
    Mix_Chunk* sound;
public:
    Sound(std::string soundPath);
    void playOnce();
    virtual ~Sound();
};


#endif //SDLBASE_SOUND_H
