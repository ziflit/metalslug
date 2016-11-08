#ifndef SDLBASE_INITIALWINDOW_H
#define SDLBASE_INITIALWINDOW_H


#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "BackgroundSprite.h"

using namespace std;

class InitialWindow {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRender;

public:
    void initializeSDL();

    SDL_Window* createWindow(const char* windowName, unsigned int window_width, unsigned int window_height);

    SDL_Renderer* createRenderer(SDL_Window* window);

    InitialWindow (unsigned int window_width, unsigned int window_height);

    SDL_Window* getMainWindow(){return InitialWindow::mainWindow;}

    SDL_Renderer* getMainRenderer(){ return InitialWindow::mainRender;}

    void showStartScreen();

};


#endif //SDLBASE_INITIALWINDOW_H
