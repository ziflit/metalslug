#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"
#define gameMusicPath "audios/circuit.wav"

//TODO: INCLUIR EN EL MAKEFILE LOS .cpp PARA QUE AQUI SE INCLUYAN UNICAMENTE LOS .h
#include "Music.cpp"
#include "Sprite.cpp"
#include "PlayerSprite.cpp"
#include "BackgroundSprite.cpp"
#include <SDL2/SDL_events.h>
#include "../../utils/Protocol.h"
#include <SDL2/SDL_events.h>

//TODO: cambiar este include je.
class SDLRunningGame {
private:
    int window_width, window_height;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Music* music;
    SDL_Texture *backgroundLayer0, *backgroundLayer1, *playersLayer;
    BackgroundSprite *backgroundSprite0, *backgroundPlayersSprite, *cloudSprite;
    PlayerSprite *player0Sprite, *player1Sprite, *player2Sprite, *player3Sprite;
    //TODO: en el destructor eliminar todos los punteros utilizados.
    int handleLeftKey, handleRightKey,handleUpKey, handleDownKey;

public:
    SDLRunningGame(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);

    SDL_Texture* createTransparentTexture(SDL_Renderer *renderer);

    void audioInitialization();

    void layersBuilding();

    void spritesBuilding();

    void updateWindowSprites();

    PlayerSprite* getPlayerSprite(){ return SDLRunningGame::player0Sprite;}

    BackgroundSprite* getBackgroundPlayerSprite(){ return SDLRunningGame::backgroundPlayersSprite;}

    struct event eventsHandler(SDL_Event* sdlEvent);

    ~SDLRunningGame();

};


#endif //SDLBASE_SDLRUNNINGGAME_H
