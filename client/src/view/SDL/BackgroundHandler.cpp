//
// Created by mfp on 10/11/16.
//

#include "BackgroundHandler.h"


BackgroundHandler::BackgroundHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}

void BackgroundHandler::addBackgroundToHandle(BackgroundSprite *newBack) {
    this->backgrounds.push_back(newBack);
}

void BackgroundHandler::handle(event newEvent) {
    BackgroundSprite* back = getBackground(newEvent.data.id);
    back->handle(newEvent);
    backgroundsToUpdate.push_back(back);
}

BackgroundSprite * BackgroundHandler::getBackground(Entity id) {

    for ( auto back : backgrounds) {
        if (back->getId() == id) {
            return back;
        }
    }
}

void BackgroundHandler::updateBottomBackgroundSprites() {
    //TODO: debe actualizar los backs 0 y 1 del nivel que este corriendo
    backgroundsToUpdate[0]->actualizarDibujo();
    backgroundsToUpdate[1]->actualizarDibujo();

}

void BackgroundHandler::updateFrontBackgroundSprite() {
    //TODO: debe actualizar el back frontal del nivel que este corriendo.
    backgroundsToUpdate[2]->actualizarDibujo();
    backgroundsToUpdate.clear();
}