#include <iostream>
#include "SDLRunningGame.cpp"

using namespace std;


int main(int argc, char *argv[]){

//____________________________________________________________________________________________
    bool running = true;
//____________________________________________________________________________________________

    SDLRunningGame sdlRunningGame = SDLRunningGame();
    sdlRunningGame.updateWindowSprites();

    sdlRunningGame.~SDLRunningGame();


    return 0;
}
