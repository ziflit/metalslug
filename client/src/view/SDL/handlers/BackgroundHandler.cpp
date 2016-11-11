//
// Created by mfp on 10/11/16.
//

#include "BackgroundHandler.h"


BackgroundHandler::BackgroundHandler() {
}

void BackgroundHandler::addBackgroundToHandle(BackgroundSprite *newBack) {
    this->backgrounds.push_back(newBack);
}

void BackgroundHandler::handle(event newEvent) {
    getBackground(newEvent.data.id)->handle(newEvent);
    this->setLevel(newEvent.data.id);
}

BackgroundSprite * BackgroundHandler::getBackground(Entity id) {
    for ( auto back : backgrounds) {
        if (back->getId() == id) {
            return back;
        }
    }
}

void BackgroundHandler::updateBottomBackgroundSprites() {
    getBack0ToUpdate()->actualizarDibujo();
    getBack1ToUpdate()->actualizarDibujo();

}

void BackgroundHandler::updateFrontBackgroundSprite() {
    getBack2ToUpdate()->actualizarDibujo();
}

void BackgroundHandler::setLevel(Entity id) {

    if (id == BACKGROUND_LVL1_Z0 || id == BACKGROUND_LVL1_Z1 || id == BACKGROUND_LVL1_Z2) {
        this->level = 1;
    }
    else if (id == BACKGROUND_LVL2_Z0 || id == BACKGROUND_LVL2_Z1 || id == BACKGROUND_LVL2_Z2) {
        this->level = 2;
    }
    else if (id == BACKGROUND_LVL3_Z0 || id == BACKGROUND_LVL3_Z1 || id == BACKGROUND_LVL3_Z2) {
        this->level = 3;
    }
}

BackgroundSprite *BackgroundHandler::getBack0ToUpdate() {
    switch (level) {
        case 1 :
            return getBackground(BACKGROUND_LVL1_Z0);
        case 2 :
            return getBackground(BACKGROUND_LVL2_Z0);
        case 3:
            return getBackground(BACKGROUND_LVL3_Z0);
    }
}

BackgroundSprite *BackgroundHandler::getBack1ToUpdate() {
    switch (level) {
        case 1 :
            return getBackground(BACKGROUND_LVL1_Z1);
        case 2 :
            return getBackground(BACKGROUND_LVL2_Z1);
        case 3:
            return getBackground(BACKGROUND_LVL3_Z1);
    }
}

BackgroundSprite *BackgroundHandler::getBack2ToUpdate() {
    switch (level) {
        case 1 :
            return getBackground(BACKGROUND_LVL1_Z2);
        case 2 :
            return getBackground(BACKGROUND_LVL2_Z2);
        case 3:
            return getBackground(BACKGROUND_LVL3_Z2);
    }
}

bool BackgroundHandler::isBackgroundType(Entity id) {
    return (id == BACKGROUND_LVL1_Z0 || id == BACKGROUND_LVL1_Z1 || id == BACKGROUND_LVL1_Z2 ||
            id == BACKGROUND_LVL2_Z0 || id == BACKGROUND_LVL2_Z1 || id == BACKGROUND_LVL2_Z2 ||
            id == BACKGROUND_LVL3_Z0 || id == BACKGROUND_LVL3_Z1 || id == BACKGROUND_LVL3_Z2 );
}
