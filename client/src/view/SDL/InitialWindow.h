#ifndef SDLBASE_INITIALWINDOW_H
#define SDLBASE_INITIALWINDOW_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>


using namespace std;

class InitialWindow {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRender;

public:
    void initializeSDL();

    void initializeMixer();

    SDL_Window* createWindow(const char* windowName);

    SDL_Renderer* createRenderer(SDL_Window* window);

    InitialWindow ();

    SDL_Window* getMainWindow(){return InitialWindow::mainWindow;}

    SDL_Renderer* getMainRenderer(){ return InitialWindow::mainRender;}

};


#endif //SDLBASE_INITIALWINDOW_H
