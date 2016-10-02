#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"
#define fps  30 //tasa de refrescamiento, fotogramas por segundo
#define speedSprite 10
#define gameMusicPath "audios/circuit.wav"


#include "AudioTools.h"
#include "SDLTools.h"
#include "Sprite.cpp"
#include "PlayerSprite.h"
#include "BackgroundSprite.h"
#include "SDLEvents.h"

class SDLRunningGame {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Mix_Music* music;
    SDL_Texture* backgroundLayer0, backgroundLayer1, playersLayer, cloudLayer;
    BackgroundSprite* backgroundSprite0, backgroundPlayersSprite, cloudSprite;
    PlayerSprite* player0Sprite,player1Sprite,player2Sprite,player3Sprite;


public:
    SDLRunningGame(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);

    void audioInitialization();

    void layersBuilding();

    void spritesBuilding();

    void updateWindowSprites();

    PlayerSprite* getPlayerSprite(){ return SDLRunningGame::playersLayer;}

    BackgroundSprite* getBackgroundPlayerSprite(){ return SDLRunningGame::backgroundPlayersSprite;}

    void ~SDLRunningGame();

};


#endif //SDLBASE_SDLRUNNINGGAME_H
