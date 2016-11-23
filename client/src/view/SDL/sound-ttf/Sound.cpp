#include "Sound.h"

Sound::Sound(std::string soundPath) {
    sound = createSound((char*)"audios/heavyMachineGun.wav" );
//    Sound::sound = createSound((soundPath);}
}
void Sound::playOnce() {
    //After this always call freeMemorySoundUsed()
    if( (Mix_PlayChannel( -1,sound, 0 )) == -1){ printf("Mix_PlayChannel: %s\n",Mix_GetError());};
    //se crea un channel para reproducir el sonido, una unica vez, loop=0
    //reproduce el sonido en el primer canal disponible que no fue reservado
}
Sound::~Sound() {
//Destructor
//It's a bad idea to free a chunk that is still being played.
    Mix_FreeChunk( Sound::sound );
    Sound::sound = NULL;
}

//SOUNDS
Mix_Chunk* Sound::createSound(char* soundPath){
   sound = NULL;
    sound = Mix_LoadWAV( soundPath );
    if( !sound ){printf( "Mix_LoadWAV: %s\n", Mix_GetError() );}
    return sound;
}