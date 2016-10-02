//
// Created by mfprado on 26/09/16.
//

#ifndef SDLBASE_SDL_EVENTS_H
#define SDLBASE_SDL_EVENTS_H


#include <SDL2/SDL_events.h>
#include <iostream>

void eventsHandler(SDL_Event event){
    if (event.type == SDL_KEYDOWN){  //si aprieto tal tecla:
        switch (event.key.keysym.sym){
            case SDLK_LEFT:
                printf("aprieto flecha izquierda");
            case SDLK_RIGHT:
                printf("aprieto flecha derecha");
            case SDLK_UP:
                printf("aprieto flecha arriba");
            case SDLK_DOWN:
                printf("aprieto flecha abajo");
        }
    }

    else if(event.type == SDL_KEYUP){   //si dejo de apretar una tecla
        switch (event.key.keysym.sym){
            case SDLK_1:
                printf("solte el 1");
        }
    }

    else if(event.type == SDL_MOUSEBUTTONDOWN){

        if (event.button.button == SDL_BUTTON_LEFT){
            printf("suelto click izq");
        }
        else if(event.button.button == SDL_BUTTON_RIGHT){
            printf("suelto click derecho");
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP){
        if(event.button.clicks == 2){ //doble click
            printf("doble click");
        }
    }

}


#endif //SDLBASE_SDL_EVENTS_H
