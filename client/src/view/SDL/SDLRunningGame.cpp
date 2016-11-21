#include "SDLRunningGame.h"

void SDLRunningGame::audioInitialization () {
    SDLRunningGame::music = new Music(gameMusicPath);
    music->play();
}

void SDLRunningGame::initializeFromXML(ConfigsXML configs) {
    this->window_width = configs.getGlobalConf().ancho;
    this->window_height = configs.getGlobalConf().alto;

    for (auto backgroundConfig : configs.getBackgroundsConfig()) {
        BackgroundSprite* newBackground = new BackgroundSprite(this->mainRenderer,
                                                               window_width,
                                                               window_height,
                                                               backgroundConfig);
        this->backgroundHandler->addBackgroundToHandle(newBackground);
    }

    for (auto playerConfig : configs.getPlayersConfig()) {
        PlayerSprite* newPlayer = new PlayerSprite(this->mainRenderer, playerConfig);
        this->playerHandler->addNewPlayer(newPlayer);
    }

    for (auto enemyConfig : configs.getEnemiesConfig()) {
        enemyHandler->newEnemyType(enemyConfig);
    }

    for (auto bulletConfig : configs.getBulletsConfig()) {
        bulletHandler->newBulletType(bulletConfig);
    }

    for (auto miscConfig : configs.getMiscelaneasConfig()) {
        miscelaneasHandler->newMscType(miscConfig);
    }

    this->scoreBoard = new ScoreBoardOrganizer(configs.getGameMode().mode, configs.getGlobalConf().cant_players, mainRenderer);
}

SDLRunningGame::SDLRunningGame(SDL_Window *mainWindow, SDL_Renderer *mainRenderer, ConfigsXML configs)  {
    this->mainWindow = mainWindow;
    this->mainRenderer = mainRenderer;
    this->playerHandler = new PlayerHandler(mainRenderer);
    this->enemyHandler = new EnemyHandler(mainRenderer);
    this->bulletHandler =new BulletHandler(mainRenderer);
    this->backgroundHandler = new BackgroundHandler();
    this->miscelaneasHandler = new MscHandler(mainRenderer);

    initializeFromXML(configs);
    SDL_GetWindowSize(mainWindow, &window_width, &window_height);
    SDLRunningGame::audioInitialization();
    holdLeftKey = holdRightKey = holdUpKey = holdDownKey = holdAKey= holdSKey = 0;
}

struct event SDLRunningGame::eventsHandler(SDL_Event* sdlEvent) {

    if (sdlEvent->type == SDL_KEYDOWN) {  //si aprieto tal tecla:
        return this->handleKeyDown(sdlEvent);
    }

    else if(sdlEvent->type == SDL_KEYUP){ //si dejo de apretar una tecla
        return this->handleKeyUp(sdlEvent);
    }

    struct event nuevoEvento;
    nuevoEvento.completion = EventCompletion::FINAL_MSG;
    nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
    return nuevoEvento;

}

void SDLRunningGame::getSpriteAndHandleNewEvent(event nuevoEvento) {

    Entity id = nuevoEvento.data.id;

    if (backgroundHandler->isBackgroundType(id)) {
        if (backgroundHandler->handle(nuevoEvento)) enemyHandler->newLevel();
        return;
    }

    if (playerHandler->isPlayerId(id)){
        playerHandler->handle(nuevoEvento);
    }

    if (enemyHandler->isEnemyType(id)) {
        enemyHandler->handle(nuevoEvento);
        return;
    }

    if (bulletHandler->isBulletType(id)) {
        bulletHandler->handle(nuevoEvento);
        return;
    }

    if (miscelaneasHandler->isMscType(id)) {
        miscelaneasHandler->handle(nuevoEvento);
        return;
    }

}

void SDLRunningGame::handleModelState(vector <event> model_state) {

        for (auto nuevoEvento : model_state){
            if (nuevoEvento.data.code == SHOW_SCOREBOARD) {
                this->scoreBoard->setData(playerHandler->getPlayers());
            } else {
                this->getSpriteAndHandleNewEvent(nuevoEvento);
            }
        }
        this->updateWindowSprites();
}


void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(this->mainRenderer);

    this->backgroundHandler->updateBottomBackgroundSprites();
    this->playerHandler->updatePlayersSprites();
    this->enemyHandler->updateEnemiesSprites();
    this->bulletHandler->updateBulletsSprites();
    this->miscelaneasHandler->updateMiscelaneaSprites();
    this->backgroundHandler->updateFrontBackgroundSprite();
    this->scoreBoard->realize();

    SDL_RenderPresent(this->mainRenderer);
}

struct event SDLRunningGame::handleKeyDown(SDL_Event* sdlEvent){
    struct event nuevoEvento;
    nuevoEvento.completion = EventCompletion::FINAL_MSG;

    switch (sdlEvent->key.keysym.sym) {
        case SDLK_LEFT:
            //holdLeftKey != 0 no volver a enviarlo al servidor
            if (holdLeftKey>0) {
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode::SDL_KEYLEFT_PRESSED;
                holdLeftKey = 1;
            }
            return nuevoEvento;
        case SDLK_RIGHT:
            if (holdRightKey>0) {
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode::SDL_KEYRIGHT_PRESSED;
                holdRightKey = 1;
            }
            return nuevoEvento;
        case SDLK_UP:
            if (holdUpKey>0) {
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode::SDL_KEYUP_PRESSED;
                holdUpKey = 1;
            }
            return nuevoEvento;
        case SDLK_DOWN:
            if (holdDownKey>0) {
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode::SDL_KEYDOWN_PRESSED;
                holdDownKey = 1;
            }
            return nuevoEvento;

        case SDLK_a:  //salto
            if (holdAKey>0){
                nuevoEvento.data.code = EventCode ::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode ::SDL_KEY_A_PRESSED;
                holdAKey= 1;
            }
            return nuevoEvento;

        case SDLK_s: //tiros
            if (holdSKey>0) {
                nuevoEvento.data.code = EventCode ::TODO_SIGUE_IGUAL;
            }
            else {
                nuevoEvento.data.code = EventCode ::SDL_KEY_S_PRESSED;
                holdSKey = 1;
            }
            return nuevoEvento;
        default:
            nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            return nuevoEvento;
    }
}

struct event SDLRunningGame::handleKeyUp(SDL_Event *sdlEvent){
    struct event nuevoEvento;
    nuevoEvento.completion = EventCompletion::FINAL_MSG;

    switch (sdlEvent->key.keysym.sym){
        case SDLK_LEFT:
            nuevoEvento.data.code = EventCode::SDL_KEYLEFT_RELEASED;
            holdLeftKey = 0;
            return nuevoEvento;
        case SDLK_RIGHT:
            nuevoEvento.data.code = EventCode::SDL_KEYRIGHT_RELEASED;
            holdRightKey = 0;
            return nuevoEvento;
        case SDLK_UP:
            nuevoEvento.data.code = EventCode::SDL_KEYUP_RELEASED;
            holdUpKey = 0;
            return nuevoEvento;
        case SDLK_DOWN:
            nuevoEvento.data.code = EventCode::SDL_KEYDOWN_RELEASED;
            holdDownKey = 0;
            return nuevoEvento;
        case SDLK_a:
            nuevoEvento.data.code = EventCode::SDL_KEY_A_RELEASED;
            holdAKey = 0;
            return nuevoEvento;
        case SDLK_s:
            nuevoEvento.data.code = EventCode::SDL_KEY_S_RELEASED;
            holdSKey = 0;
            return nuevoEvento;
        default:
            nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            return nuevoEvento;

    }
}

SDLRunningGame::~SDLRunningGame () {

    delete playerHandler;
    delete enemyHandler;
    delete bulletHandler;
    delete backgroundHandler;
    delete miscelaneasHandler;
    delete music;
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}