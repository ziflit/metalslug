#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define gameMusicPath "audios/musicGame.mp3"
#include "sound-ttf/Music.h"
#include <vector>
#include "spriteClasses/BackgroundSprite.h"
#include "spriteClasses/PlayerSprite.h"
#include "spriteClasses/EnemySprite.h"
#include "handlers/EnemyHandler.h"
#include <SDL2/SDL_events.h>
#include "../../model/ConfigsXML.h"
#include "handlers/BulletHandler.h"
#include "handlers/BackgroundHandler.h"
#include "handlers/MscHandler.h"

class SDLRunningGame {
private:
    int window_width, window_height;
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Music* music;
    int holdLeftKey, holdRightKey,holdUpKey, holdDownKey, holdAKey,holdSKey;
    vector<PlayerSprite*> playersSprites;
    EnemyHandler* enemyHandler;
    BulletHandler *bulletHandler;
    BackgroundHandler *backgroundHandler;
    MscHandler *miscelaneasHandler;

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


    void resetStatus();
};


#endif //SDLBASE_SDLRUNNINGGAME_H
