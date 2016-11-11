#include <zconf.h>
#include "InitialWindow.h"

void InitialWindow::initializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        //inicializa TIMER, VIDEO, AUDIO, JOISTICK, HAPTIC,GAMECONTROLLER, EVENTS...
        cout<<"There was error initializing SDL: "<< endl
            <<SDL_GetError() << endl;
    }
    if(TTF_Init() < 0){
        cout<<"There was error initializig TTF: "<< TTF_GetError()<<endl;
    }
}

SDL_Window* InitialWindow::createWindow(const char *windowName, unsigned int window_width, unsigned int window_height) {
    SDL_Window *window = SDL_CreateWindow(windowName,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height,
                                          0);  //Este 0 = Not Resizable, para Resizable = SDL_WINDOW_RESIZABLE


    if(window == NULL){
        cout<<"There was error initializing the window: "<< endl
            <<SDL_GetError() << endl;
    }

    return window;

}

SDL_Renderer* InitialWindow::createRenderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        cout<<"There was error creating renderer: "<<SDL_GetError()<<endl;
    }
    return renderer;

}

InitialWindow::InitialWindow(unsigned int window_width, unsigned int window_height) {
    InitialWindow::initializeSDL();
    InitialWindow::mainWindow = createWindow("METAL SLUG",window_width,window_height);
    InitialWindow::mainRender = createRenderer(InitialWindow::mainWindow);
}


void InitialWindow::showStartScreen() {
    BackgroundSprite* startBack = new BackgroundSprite(mainRender,800,600);
    startBack->setUpImage("sprites/backgrounds/startScreen.png");
    startBack->setSourceRectWidth(startBack->getSpriteImageWidth()/2);
    startBack->setSourceRectHeight(startBack->getSpriteImageHeight());
    SDL_Event evento;
    SDL_RenderClear(this->mainRender);
    bool enterPressed = false;

    while(!enterPressed){
        startBack->setNextStartBackFrame();
        startBack->actualizarDibujo();
        SDL_RenderPresent(mainRender);


        usleep(100000);

        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_KEYDOWN and evento.key.keysym.sym == SDLK_RETURN){
                cout<<"ENTRO AL PRESSED ENTER"<<endl;
                enterPressed = true;

            }
        }
    }

    BackgroundSprite* waitingPlayers = new BackgroundSprite(mainRender,800,600);
    waitingPlayers->setUpImage("sprites/backgrounds/waitingPlayers.png");
    waitingPlayers->setSourceRectWidth(startBack->getSpriteImageWidth());
    waitingPlayers->setSourceRectHeight(startBack->getSpriteImageHeight());
    SDL_RenderClear(this->mainRender);
    waitingPlayers->actualizarDibujo();
    SDL_RenderPresent(mainRender);

    delete startBack;

}
