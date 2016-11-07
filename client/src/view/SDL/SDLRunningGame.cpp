#include "SDLRunningGame.h"

void SDLRunningGame::audioInitialization () {
    //Audio Initialization
    SDLRunningGame::music = new Music(gameMusicPath);
    music->play();
}

void SDLRunningGame::initializeFromXML(ConfigsXML configs) {
    this->window_width = configs.getGlobalConf().ancho;
    this->window_height = configs.getGlobalConf().alto;

    vector<xmlBackground> backgroundConfigs = configs.getBackgroundsConfig();

    for (auto backgroundConfig : backgroundConfigs) {
        BackgroundSprite* newBackground = new BackgroundSprite(this->mainRenderer,
                                                               window_width,window_height);
        newBackground->setUpImage(backgroundConfig.path);
        newBackground->setId(backgroundConfig.id);
        this->backgroundSprites.push_back(newBackground);
    }

    for (auto playerConfig : configs.getPlayersConfig()) {
        PlayerSprite* newPlayer = new PlayerSprite(this->mainRenderer,
                                                   window_width, window_height);
        newPlayer->setWidth(playerConfig.ancho);
        newPlayer->setHeight(playerConfig.alto);
        newPlayer->setId(playerConfig.id);
        newPlayer->setUpImage(playerConfig.pathColor,playerConfig.pathGrey,
                              playerConfig.cantWidthFrames,playerConfig.cantHeightFrames);
        newPlayer->setUpWeaponsImage(playerConfig.pathWeapons);
        this->playersSprites.push_back(newPlayer);
    }

    for (auto enemyConfig : configs.getEnemiesConfig()) {
        EnemySprite* newEnemy = new EnemySprite(this->mainRenderer,
                                                   window_width, window_height);
        newEnemy->setWidth(enemyConfig.ancho);
        newEnemy->setHeight(enemyConfig.alto);
        newEnemy->setId(enemyConfig.id);
        newEnemy->setUpImage(enemyConfig.path, enemyConfig.cantWidthFrames, enemyConfig.cantHeightFrames);
        this->enemiesSprites.push_back(newEnemy);
    }
}

SDLRunningGame::SDLRunningGame(SDL_Window *mainWindow, SDL_Renderer *mainRenderer, ConfigsXML configs)  {
    SDLRunningGame::mainWindow = mainWindow;
    SDLRunningGame::mainRenderer = mainRenderer;
    initializeFromXML(configs);
    SDL_GetWindowSize(mainWindow, &window_width, &window_height);

    SDLRunningGame::audioInitialization();

    holdLeftKey = holdRightKey = holdUpKey = holdDownKey = holdAKey= holdSKey = 0;

}

struct event SDLRunningGame::handleKeyDown(SDL_Event* sdlEvent){
    struct event nuevoEvento;
    nuevoEvento.completion = EventCompletion::FINAL_MSG;

    switch (sdlEvent->key.keysym.sym){
        case SDLK_LEFT:
            //holdLeftKey != 0 no volver a enviarlo al servidor
            if(holdLeftKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYLEFT_PRESSED;
                holdLeftKey = 1;
            }
            return nuevoEvento;
        case SDLK_RIGHT:
            if(holdRightKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYRIGHT_PRESSED;
                holdRightKey = 1;
            }
            return nuevoEvento;
        case SDLK_UP:
            if(holdUpKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYUP_PRESSED;
                holdUpKey = 1;
            }
            return nuevoEvento;
        case SDLK_DOWN:
            if(holdDownKey>0){
                nuevoEvento.data.code = EventCode::TODO_SIGUE_IGUAL;
            }
            else{
                nuevoEvento.data.code = EventCode::SDL_KEYDOWN_PRESSED;
                holdDownKey = 1;
            }
            return nuevoEvento;

        case SDLK_a:  //salto
            if(holdAKey>0){
                nuevoEvento.data.code = EventCode ::TODO_SIGUE_IGUAL;
            }
            else{
                nuevoEvento.data.code = EventCode ::SDL_KEY_A_PRESSED;
                holdAKey= 1;
            }
            return nuevoEvento;

        case SDLK_s: //tiros
            if(holdSKey>0){
                nuevoEvento.data.code = EventCode ::TODO_SIGUE_IGUAL;
            }
            else{
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

void SDLRunningGame::getSpriteAndSendNewEvent(event nuevoEvento) {
    Entity id = nuevoEvento.data.id;

    for (auto back : backgroundSprites) {
        if(back->getId() == id){
            back->handle(nuevoEvento);
        }
    }
    for (auto player : playersSprites) {
        if ( player->getId() == id ){
            player->handle(nuevoEvento);
        }
    }
    for (auto enemy : enemiesSprites) {
        if ( enemy->getId() == id ){
            enemy->handle(nuevoEvento);
        }
    }

    //TODO: importante ver el dibujo de las balas, no debe cargar la imagen por cada nueva.
}

void SDLRunningGame::handleModelState(vector <event> model_state) {

        for (auto nuevoEvento : model_state){

            this->getSpriteAndSendNewEvent(nuevoEvento);
        }

        //TODO: aqui se debe manejar el dibujo de balas y cajas.
        //TODO: tambien aqui se debe manejar la destruccion de sprites que no deben dibujarse mas.

        this->updateWindowSprites();
}


void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(this->mainRenderer);

    for (int i = 0 ; i < (backgroundSprites.size()-1) ; i++) {
        backgroundSprites[i]->actualizarDibujo();
    }

    for (int i = 0 ; i< playersSprites.size() ; i++) {  //ojo con el auto, le ponia por defecto tipo Sprite cuando es PlayerSprite
            playersSprites[i]->actualizarDibujo();
    }

    for (int i = 0 ; i< enemiesSprites.size() ; i++) {  //ojo con el auto, le ponia por defecto tipo Sprite cuando es EnemySprite
        enemiesSprites[i]->actualizarDibujo();
    }


   backgroundSprites[(backgroundSprites.size() - 1)]->actualizarDibujo();

    SDL_RenderPresent(this->mainRenderer);
}

//DESTRUCTOR
SDLRunningGame::~SDLRunningGame () {

    for (auto playerSprite : playersSprites){
        delete playerSprite;
    }

    for (auto enemySprite : enemiesSprites){
        delete enemySprite;
    }

    for (auto backSprite : backgroundSprites){
        delete backSprite;
    }

    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}
