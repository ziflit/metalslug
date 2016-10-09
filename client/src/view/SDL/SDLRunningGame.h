#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"
#define fps  30 //tasa de refrescamiento, fotogramas por segundo
#define speedSprite 10
#define gameMusicPath "audios/circuit.wav"

//TODO: incluir en el makefile .cpp para cambiar los siguientes por .h
#include "Music.cpp"
#include "Sprite.cpp"
#include "PlayerSprite.cpp"
#include "BackgroundSprite.cpp"
#include <SDL2/SDL_events.h>

class SDLRunningGame {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Music* music;
    SDL_Texture *backgroundLayer0, *backgroundLayer1, *playersLayer, *cloudLayer;
    BackgroundSprite *backgroundSprite0, *backgroundPlayersSprite, *cloudSprite;
    PlayerSprite *player0Sprite, *player1Sprite, *player2Sprite, *player3Sprite;
    //TODO: en el destructor eliminar todos los punteros utilizados.
    int handleLeftKey, handleRightKey;


public:
    SDLRunningGame(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);

    SDL_Texture* createTransparentTexture(SDL_Renderer *renderer);

    void audioInitialization();

    void layersBuilding();

    void spritesBuilding();

    void updateWindowSprites();

    PlayerSprite* getPlayerSprite(){ return SDLRunningGame::player0Sprite;}

    BackgroundSprite* getBackgroundPlayerSprite(){ return SDLRunningGame::backgroundPlayersSprite;}

    void eventsHandler(SDL_Event* event);




    ~SDLRunningGame();

};


#endif //SDLBASE_SDLRUNNINGGAME_H
