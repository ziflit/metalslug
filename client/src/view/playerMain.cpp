//
// Created by mfprado on 01/10/16.
//
#include "SDLToold.h"
using namespace std;



int main(int argc, char *argv[]){
    bool running = false;
    /* INICIALIZAR CONECCION CON EL SERVER
     * CARGAR EL ESCENARIO
     * ESPERAR A QUE SE CONECTEN TODOS LOS PLAYERS DE LA PARTIDA
     */
    //then running = true;


    initializeSDL(running);
    SDLRunningGame* sdlRunningGame = SDLRunnigGame(mainWindow, mainRenderer);


    /*
     * Crear cada jugador y el mapa de juego.
     * Para asignar los sprites: SDLRunningGame::getSpritePlayer(), SDLRunningGame::getBackgrpund()
     */


    /* ARMAR LA FRECUENCIA DE ACTUALIZACION
     * sdlRunnigGame->updateWindowSprites();
     *
     */


    return 0;
}