//
// Created by mfprado on 30/09/16.
//

#include "InitialWindow.h"

InitialWindow::InitialWindow (bool* running, SDL_Window *mainWindow, SDL_Renderer *mainRenderer) {
    initializeMixer();
    initializeSDL(running);
    InitialWindow::mainWindow = createWindow("METAL SLUG");
    InitialWindow::mainRender = createRenderer(InitialWindow::mainWindow);
}