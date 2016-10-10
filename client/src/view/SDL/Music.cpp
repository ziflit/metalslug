//
// Created by mfprado on 08/10/16.
//

#include "Music.h"

#define FOREVER -1

Music::Music(std::string musicPath){
//El mixer soporta un solo canal para "Music"
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
