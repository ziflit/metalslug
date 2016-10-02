#include <iostream>
#include "SDL/AudioTools.h"
#include "SDL/SDLTools.h"
#include "SDL/Sprite.cpp"
#include "SDL/PlayerSprite.cpp"
#include "SDL/BackgroundSprite.cpp"
#include "SDL/SDLEvents.h"

using namespace std;


int main(int argc, char *argv[]){

//____________________________________________________________________________________________
    bool running = true;
    initializeSDL(&running);
//____________________________________________________________________________________________

    SDL_Window* mainWindow = createWindow((char*)"METAL SLUG");
    SDL_Renderer* mainRenderer = createRenderer(mainWindow);

    SDL_Texture* backgroundLayer0 = createTransparentTexture(mainRenderer);
    SDL_Texture* backgroundLayer1 = createTransparentTexture(mainRenderer);
    SDL_Texture* layerCloud = createTransparentTexture(mainRenderer);
    SDL_Texture* layerPlayer = createTransparentTexture(mainRenderer);
//____________________________________________________________________________________________

    BackgroundSprite backgroundSprite0 = BackgroundSprite(backgroundLayer0,mainRenderer);
    backgroundSprite0.setUpImage("sprites/backgrounds/backgroundMetal1.png");

    BackgroundSprite backgroundSprite1 = BackgroundSprite(backgroundLayer1,mainRenderer);
    backgroundSprite1.setUpImage("sprites/backgrounds/backgroundMetal2.png");
    backgroundSprite1.set_position(0,window_height/2);
    backgroundSprite1.setHeight(window_height/2);

    BackgroundSprite cloud = BackgroundSprite(layerCloud,mainRenderer);
    cloud.setUpImage("sprites/backgrounds/nube.png");
    cloud.setWidth(200);
    cloud.setHeight(80);
    cloud.set_position(0,100);

    PlayerSprite player = PlayerSprite(layerPlayer,mainRenderer);
    player.setUpImage("sprites/marco.png",9,6);

//____________________________________________________________________________________________
    initializeMixer();

    Mix_Chunk *sound = createSound((char*)"audios/wind.wav" );
    playSoundManyTimes(sound,2);

    Mix_Music *music = createMusic((char*) "audios/circuit.wav" );
    playMusicForever(music);

//____________________________________________________________________________________________


    Uint32  starting_tick;
    SDL_Event event;

    while( running ){

//____________________________________________________________________________________________

        backgroundSprite0.increaseFrameTime();

        if(fps / (backgroundSprite0.getFrameTime()) == 10){
            backgroundSprite0.setNextSpriteFrame();
            backgroundSprite0.restartFrameTime();

            if(cloud.getXPosition()==window_width){
                cloud.set_position(0,cloud.getYPosition());
            }
            cloud.set_position(cloud.getXPosition()+1,cloud.getYPosition());
        }

//____________________________________________________________________________________________


        starting_tick = SDL_GetTicks();


        while (SDL_PollEvent( &event )){
            if ( event.type == SDL_QUIT) {
                running = false;
                break;
            }



//____________________________________________________________________________________________

            player.increaseFrameTime();

//____________________________________________________________________________________________

            if(fps / player.getFrameTime() == 30 ){

                player.handlePlayerEvents(event,&backgroundSprite1);
                player.restartFrameTime();


            }
//____________________________________________________________________________________________
        }

        cap_framerate(starting_tick);  //maneja los delays del loop que actualiza la salida de todo el SDL


        SDL_RenderClear(mainRenderer);

        backgroundSprite0.update();
        backgroundSprite1.update();
        player.update();
        cloud.update();

        SDL_RenderPresent(mainRenderer);

    }
//____________________________________________________________________________________________

    //Liberar todo

    SDL_DestroyTexture(backgroundLayer0);
    SDL_DestroyTexture(backgroundLayer1);
    SDL_DestroyTexture(layerCloud);
    SDL_DestroyTexture(layerPlayer);
    SDL_DestroyRenderer(mainRenderer);
    freeMemorySoundUsed(sound);
    Mix_CloseAudio();   //Shutdown and cleanup the mixer API
//____________________________________________________________________________________________
    SDL_DestroyWindow(mainWindow);
    SDL_Quit( );
    return 0;
}
