#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define gameMusicPath "audios/musicGame.mp3"
#include "Music.h"
#include <vector>
#include "SpritesClasses.h"
#include <SDL2/SDL_events.h>
#include "../../model/Configs.h"

class SDLRunningGame {
private:
    Configs configs;
    int window_width, window_height;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Music* music;
    SDL_Texture *backgroundLayer0, *backgroundLayer1, *backgroundLayer2, *playersLayer;
    BackgroundSprite *backgroundSprite0, *backgroundSprite1, *backgroundSprite2;
    PlayerSprite *marcoSprite, *tarmaSprite, *fioSprite, *eriSprite;
    //TODO: en el destructor eliminar todos los punteros utilizados.
    int holdLeftKey, holdRightKey,holdUpKey, holdDownKey, holdAKey,holdSKey;

public:
    SDLRunningGame(SDL_Window* mainWindow, SDL_Renderer* mainRenderer, Configs configs );

    SDL_Texture* createTransparentTexture(SDL_Renderer *renderer);

    void audioInitialization();

    void layersBuilding();

    void spritesBuilding();

    void updateWindowSprites();

    void initializeMarco();

    void initializeTarma();

    void initializeFio();

    void initializeEri();

    PlayerSprite* getMarcoSprite(){ return SDLRunningGame::marcoSprite;}

    struct event eventsHandler(SDL_Event* sdlEvent);

    virtual~SDLRunningGame();

    void handleModelState(vector<struct event> model_state);

};


#endif //SDLBASE_SDLRUNNINGGAME_H
