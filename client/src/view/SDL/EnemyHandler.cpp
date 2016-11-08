//
// Created by mfp on 08/11/16.
//

#include "EnemyHandler.h"


EnemyHandler::EnemyHandler(SDL_Window *mainWindow, SDL_Renderer *mainRenderer, int window_width, int window_height) {

}

void EnemyHandler::newEnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames,
                                int cantHeightFrames) {
    enemiesTypes.push_back(
            new EnemyType(ancho, alto, id, imagePath, cantWidthFrames, cantHeightFrames)
    );

}

bool EnemyHandler::isEnemyType(Entity id) {
    return false;
}

void EnemyHandler::handle(event event) {

}
