#include "SDLRunningGame.h"

void SDLRunningGame::audioInitialization () {
    //Audio Initialization

    SDLRunningGame::music = createMusic((char *) gameMusicPath);
    playMusicForever(SDLRunningGame::music);

}
void SDLRunningGame::layersBuilding (){
    //Layers Building
    SDLRunningGame::backgroundLayer0 = createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundLayer1 = createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudLayer = createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::playerLayer = createTransparentTexture(SDLRunningGame::mainRenderer);
}
void SDLRunningGame::spritesBuilding () {
    //Sprites Building
    SDLRunningGame::backgroundSprite0 = BackgroundSprite(SDLRunningGame::backgroundLayer0,
                                                         SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundLayer0.setUpImage("sprites/backgrounds/backgroundMetal1.png");

    SDLRunningGame::backgroundSprite1 = BackgroundSprite(SDLRunningGame::backgroundLayer1,
                                                         SDLRunningGame::mainRenderer);
    backgroundSprite1.setUpImage("sprites/backgrounds/backgroundMetal2.png");
    backgroundSprite1.set_position(0, window_height / 2);
    backgroundSprite1.setHeight(window_height / 2);

    SDLRunningGame::cloudSprite = BackgroundSprite(SDLRunningGame::cloudLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudSprite.setUpImage("sprites/backgrounds/nube.png");
    SDLRunningGame::cloudSprite.setWidth(200);
    SDLRunningGame::cloudSprite.setHeight(80);
    SDLRunningGame::cloudSprite.set_position(0, 100);

    SDLRunningGame::playerSprite = PlayerSprite(SDLRunningGame::playerLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::playerSprite.setUpImage("sprites/examplePlayerSprite.png", 3, 4);
}

SDLRunningGame::SDLRunningGame (SDL_Window *mainWindow, SDL_Renderer *mainRenderer) {
    SDLRunningGame::mainWindow = mainWindow;
    SDLRunningGame::mainRenderer = mainRenderer;
//_______________________________________________________________________________________
   SDLRunningGame::layersBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::spritesBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::audioInitialization();
//____________________________________________________________________________________________

}


void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(SDLRunningGame::mainRenderer);

    SDLRunningGame::backgroundSprite0.update();
    SDLRunningGame::backgroundSprite1.update();
    SDLRunningGame::playerSprite.update();
    SDLRunningGame::cloudSprite.update();

    SDL_RenderPresent(SDLRunningGame::mainRenderer);
}

//DESTRUCTOR
SDLRunningGame::~SDLRunningGame () {
//____________________________________________________________________________________________
    //Liberar todo

    SDL_DestroyTexture(SDLRunningGame::backgroundLayer0);
    SDL_DestroyTexture(SDLRunningGame::backgroundLayer1);
    SDL_DestroyTexture(SDLRunningGame::cloudLayer);
    SDL_DestroyTexture(SDLRunningGame::playersLayer);
    SDL_DestroyRenderer(SDLRunningGame::mainRenderer);
    closeMixer();   //Shutdown and cleanup the mixer API
//____________________________________________________________________________________________
    SDL_DestroyWindow(SDLRunningGame::mainWindow);
    SDL_Quit();
}


