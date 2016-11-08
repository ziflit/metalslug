#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define gameMusicPath "audios/musicGame.mp3"
#include "Music.h"
#include <vector>
#include "BackgroundSprite.h"
#include "PlayerSprite.h"
#include "EnemySprite.h"
#include <SDL2/SDL_events.h>
#include "../../model/ConfigsXML.h"

class SDLRunningGame {
private:
    int window_width, window_height;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Music* music;
    int holdLeftKey, holdRightKey,holdUpKey, holdDownKey, holdAKey,holdSKey;
    vector<BackgroundSprite*> backgroundSprites;
    vector<PlayerSprite*> playersSprites;
    vector<EnemySprite*> enemiesSprites;


    event handleKeyDown(SDL_Event *sdlEvent);

    event handleKeyUp(SDL_Event *sdlEvent);

    void initializeFromXML(ConfigsXML configs);

    void audioInitialization();

    void getSpriteAndHandleNewEvent(event nuevoEvento);

public:

    SDLRunningGame(SDL_Window* mainWindow, SDL_Renderer* mainRenderer, ConfigsXML configs );

    void updateWindowSprites();

    struct event eventsHandler(SDL_Event* sdlEvent);

    virtual~SDLRunningGame();

    void handleModelState(vector<struct event> model_state);
};


#endif //SDLBASE_SDLRUNNINGGAME_H
