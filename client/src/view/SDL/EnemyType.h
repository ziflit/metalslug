//
// Created by mfp on 08/11/16.
//

#ifndef METALSLUG_ENEMYTYPE_H
#define METALSLUG_ENEMYTYPE_H


#include "../../utils/Protocol.h"

class EnemyType {
private:

    int ancho;
    int alto;
    Entity id;
    int cantWidthFrames, cantHeigthFrames;

public:

    EnemyType(int ancho, int alto, Entity id, char *imagePath, int cantWidthFrames, int cantHeightFrames);
};


#endif //METALSLUG_ENEMYTYPE_H
