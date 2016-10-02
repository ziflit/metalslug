//
// Created by mfprado on 25/09/16.
//

#ifndef SDLBASE_AUDIOTOOLS_H
#define SDLBASE_AUDIOTOOLS_H


#include <SDL2/SDL_mixer.h>
#include "SDL2/SDL_mixer.h"
#include <iostream>

/*SDL_mixer is a sample multi-channel audio mixer library
 * It suports any number of simultaneously playing channels of 16 bits stereo audio
 * plus a single channel of music(Mix_Music).
 *
 * SDL_mixer suports the following formats:
 * .wav, .aiff, .voc, .mod, .mid, .ogg, .mp3, .flac
 *
 * To compile you need to link the libraries adding: -lSDL2_mixer
 * Example: g++ myprogram.cpp `pkg-config --cflags --libs sdl2` -lSDL2_mixer
*/


void initializeMixer() {
    if( ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 ) ) == -1 ){
        //2-> set for stereo or 1 for mono, 4096->magia negra
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    };
}

void closeMixer(){Mix_CloseAudio();}

const char * getLastMixAudioError(){ return Mix_GetError(); }

void setSoundVolume(Mix_Chunk *sound, int volume){
    //if volume < 0 then this volume is still the current volume for de chunk/sound
    //if volume > MIX_MAX_VOLUME = 128 the this volume will be 128
    //int previousVolume = Mix_VolumeChunk(sound,volume);
    Mix_VolumeChunk(sound, volume);
}

//_________________________________________________________________________________________________________
    //MUSIC
Mix_Music* createMusic(char* musicPath) {
    //El mixer soporta un solo canal para "Music"
    Mix_Music *music = NULL;
    music = Mix_LoadMUS(musicPath);
    return music;
}

void playMusicForever(Mix_Music* music){Mix_PlayMusic(music, -1);} //-1-> play music forever

void setMusicVolume(int volume){Mix_VolumeMusic(volume);}

void pauseMusic(){Mix_PauseMusic();}

//_________________________________________________________________________________________________________
    //SOUNDS
Mix_Chunk* createSound(char* soundPath){
    Mix_Chunk *sound = NULL;
    sound = Mix_LoadWAV( soundPath );
        if( !sound ){printf( "Mix_LoadWAV: %s\n", Mix_GetError() );}
    return sound;
}

void freeMemorySoundUsed(Mix_Chunk* sound){
//Destructor
//It's a bad idea to free a chunk that is still being played.
Mix_FreeChunk( sound );
sound = NULL;
}

void playSoundOnce(Mix_Chunk *sound){
    //After this always call freeMemorySoundUsed()
    if( (Mix_PlayChannel( -1,sound, 0 )) == -1){ printf("Mix_PlayChannel: %s\n",getLastMixAudioError());};
    //se crea un channel para reproducir el sonido, una unica vez, loop=0
    //reproduce el sonido en el primer canal disponible que no fue reservado
}

void playSoundOnceTimed(Mix_Chunk *sound, int ticks){
    //After this always call freeMemorySoundUsed()
    //ticks = 1000, the sound will be played by 1 second.
    Mix_PlayChannelTimed(-1,sound,-1,ticks);}

void playSoundManyTimes(Mix_Chunk* sound, int times){
    //After this always call freeMemorySoundUsed()
    Mix_PlayChannel( -1,sound,times-1 );  //reproduce el sonido en el primer canal disponible que no fue reservado
}

void pauseAllSounds(){Mix_Pause(-1);}

void resumePlayindAllSounds(){Mix_Resume(-1);}

#endif //SDLBASE_AUDIOTOOLS_H
