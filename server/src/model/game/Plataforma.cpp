/*
 * Plataforma.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: fpirra
 */

#include "Plataforma.h"

Plataforma::Plataforma(int posX, int posY, int ancho, int largo) {
    id = MSC_PLATFORM;
    x = posX;
    y = posY;
    box_ancho = ancho;
    box_alto = largo;
}

Plataforma::~Plataforma() {
	// TODO Auto-generated destructor stub
}

