//
// Created by mfp on 08/11/16.
//

#include "EnemyType.h"

EnemyType::EnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames) {
    this->ancho = ancho;
    this->alto = alto;
    this->id = id;
    this->cantWidthFrames = cantWidthFrames;
    this->cantHeigthFrames = cantHeightFrames;


}