#include "SDLRunningGame.h"

void SDLRunningGame::audioInitialization () {
    //Audio Initialization
    SDLRunningGame::music = new Music(gameMusicPath);
    music->play();
}

SDL_Texture* SDLRunningGame::createTransparentTexture(SDL_Renderer *renderer){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(backgroundTransparentPath);

    if(loadingSurface == NULL)
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;

    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        if(backgroundTexture == NULL){
            cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

        }

        SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
        return backgroundTexture;
    }
    return backgroundTexture;
}

void SDLRunningGame::layersBuilding (){
    //Layers Building
    SDLRunningGame::backgroundLayer0 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundLayer1 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudLayer = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::playersLayer = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
}

void SDLRunningGame::spritesBuilding () {
    //Sprites Building
    SDLRunningGame::backgroundSprite0 = new BackgroundSprite(SDLRunningGame::backgroundLayer0,
                                                         SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundSprite0->setUpImage("sprites/backgrounds/backgroundMetal1.png");

    SDLRunningGame::backgroundPlayersSprite = new BackgroundSprite(SDLRunningGame::backgroundLayer1,
                                                         SDLRunningGame::mainRenderer);
    backgroundPlayersSprite->setUpImage("sprites/backgrounds/backgroundMetal2.png");
    backgroundPlayersSprite->set_position(0, window_height / 2);
    backgroundPlayersSprite->setHeight(window_height / 2);

    SDLRunningGame::cloudSprite = new BackgroundSprite(SDLRunningGame::cloudLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudSprite->setUpImage("sprites/backgrounds/nube.png");
    SDLRunningGame::cloudSprite->setWidth(200);
    SDLRunningGame::cloudSprite->setHeight(80);
    SDLRunningGame::cloudSprite->set_position(0, 100);

    SDLRunningGame::player0Sprite = new PlayerSprite(SDLRunningGame::playersLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::player0Sprite->setUpImage("sprites/marco.png", 12, 10);
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
    SDLRunningGame::handleLeftKey = SDLRunningGame::handleRightKey = 0;
}

void SDLRunningGame::eventsHandler(SDL_Event* event) {


    if (event->type == SDL_KEYDOWN){  //si aprieto tal tecla:
        switch (event->key.keysym.sym){
            case SDLK_LEFT:
                printf("aprieto flecha izquierda");
                SDLRunningGame::player0Sprite->moveLeft();
                SDLRunningGame::handleLeftKey+=1;
                break;
            case SDLK_RIGHT:
                printf("aprieto flecha derecha");
                SDLRunningGame::player0Sprite->moveRight();
                SDLRunningGame::handleRightKey+=1;
                break;
            case SDLK_UP:
                printf("aprieto flecha arriba");
                break;
            case SDLK_DOWN:
                printf("aprieto flecha abajo");
                break;
        }
    }

    else if(event->type == SDL_KEYUP){   //si dejo de apretar una tecla
        switch (event->key.keysym.sym){
            case SDLK_LEFT:
                cout<<("solte la tecla izq")<<endl;
                cout<<(SDLRunningGame::handleLeftKey)<<endl;
                //TODO: ENVIAR MENSAJE AL SERVER QUE APRETO "handleLeftKey" CANTIDAD DE VECES "LEFT ARROW"
                SDLRunningGame::handleLeftKey = 0;
                break;
            case SDLK_RIGHT:
                cout<<"solte la flecha der"<<endl;
                cout<<SDLRunningGame::handleRightKey<<endl;
                //TODO: ENVIAR MENSAJE AL SERVER QUE APRETO "handleRightKey" CANTIDAD DE VECES "RIGHT ARROW"
            SDLRunningGame::handleRightKey = 0;
        }
    }

    else if(event->type == SDL_MOUSEBUTTONDOWN){
        switch (event->button.button){

            case SDL_BUTTON_LEFT:
            printf("suelto click izq");
            break;

            case SDL_BUTTON_RIGHT:
            printf("suelto click derecho");
            break;
        }
    }

//    else if(event->type == SDL_MOUSEBUTTONUP){
//        if(event->button.clicks == 2){ //doble click
//            printf("doble click");
//        }
//    }
}

void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(SDLRunningGame::mainRenderer);

    SDLRunningGame::backgroundSprite0->update();
    SDLRunningGame::backgroundPlayersSprite->update();
    SDLRunningGame::player0Sprite->update();
    SDLRunningGame::cloudSprite->update();

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
//    closeMixer();   //ESTA EN EL DESTRUCTOR DE MUSIC
//____________________________________________________________________________________________
    SDL_DestroyWindow(SDLRunningGame::mainWindow);
    SDL_Quit();
}


