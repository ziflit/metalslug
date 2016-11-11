#ifndef SDLBASE_MUSIC_H
#define SDLBASE_MUSIC_H


#include <SDL2/SDL_mixer.h>
#include <string>

class Music{
private:
    Mix_Music* piece;
public:

    void initializeMixer();
    Music(std::string musicPath);
    void play();
    void changeTrack(std::string file);
    void stop();
    void pause();
    void pauseAllSounds(){Mix_Pause(-1);}
    void resumePlayingAllSounds(){Mix_Resume(-1);}
    ~Music();
};


#endif //SDLBASE_MUSIC_H
