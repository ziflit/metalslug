//
// Created by mfprado on 30/09/16.
//

#ifndef SDLBASE_INITIALWINDOW_H
#define SDLBASE_INITIALWINDOW_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"

#include "SDLTools.h"

class InitialWindow {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRender;

public:
    InitialWindow (bool* running, SDL_Window* mainWindow, SDL_Renderer* mainRenderer);

    SDL_Window* getMainWindow(){return InitialWindow::mainWindow;}

    SDL_Renderer* getMainRenderer(){ return InitialWindow::mainRender;}

    void evetsHanddler(SDL_Event event);
};


#endif //SDLBASE_INITIALWINDOW_H
