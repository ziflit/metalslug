#include "InitialWindow.h"

void InitialWindow::initializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        //inicializa TIMER, VIDEO, AUDIO, JOISTICK, HAPTIC,GAMECONTROLLER, EVENTS...
        cout<<"There was error initializing SDL: "<< endl
            <<SDL_GetError() << endl;
    }
}

SDL_Window* InitialWindow::createWindow(const char *windowName, unsigned int window_width, unsigned int window_height) {
    SDL_Window *window = SDL_CreateWindow(windowName,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height,
                                          SDL_WINDOW_RESIZABLE);


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

void InitialWindow::initializeMixer() {
    if( ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 ) ) == -1 ){
        //2-> set for stereo or 1 for mono, 4096->magia negra
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    };
}

InitialWindow::InitialWindow(unsigned int window_width, unsigned int window_height) {
    InitialWindow::initializeMixer();
    InitialWindow::initializeSDL();
    InitialWindow::mainWindow = createWindow("METAL SLUG",window_width,window_height);
    InitialWindow::mainRender = createRenderer(InitialWindow::mainWindow);
}
