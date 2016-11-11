#include "Music.h"

#define FOREVER -1

void Music::initializeMixer() {
    if ((Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) == -1) {
        //2-> set for stereo or 1 for mono, 4096->magia negra
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    }
}

Music::Music(std::string musicPath){
//El mixer soporta un solo canal para "Music"
    initializeMixer();
    piece = NULL;
    piece = Mix_LoadMUS(musicPath.c_str());
}

void Music::play(){
    Mix_PlayMusic(piece, FOREVER);
}


void Music::pause(){Mix_PauseMusic();}

void Music::changeTrack(std::string file){
    if (piece){
        Mix_FreeMusic(piece);
        piece = NULL;
    }
    piece = Mix_LoadMUS(file.c_str());
}

void Music::stop(){
    Mix_HaltMusic();
}

Music::~Music(){
    if(piece)
        Mix_FreeMusic(piece);
    piece = NULL;
    Mix_CloseAudio();
}
