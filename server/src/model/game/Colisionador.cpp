/*
 * Colisionador.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: fpirra
 */

#include "Colisionador.h"

Colisionador::Colisionador() {
	// TODO Auto-generated constructor stub

}

Colisionador::~Colisionador() {
	// TODO Auto-generated destructor stub
}

vector<GameObject*> Colisionador::cualesColisionan(vector<GameObject*> objetosParaColisionar) {
    for (auto objeto: objetosParaColisionar) {
    	//Una opcion es dividir la pantalla en cuadrados grandes, y solo verificar
    	// las colisiones de los objetos que se encuentren en los mismos cuadrados o zonas...
    	//esto tiene que aumentar la velocidad
    }
}
