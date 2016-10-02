#ifndef SDLBASE_SDLTOOLS_H
#define SDLBASE_SDLTOOLS_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"
#define fps  30 //tasa de refrescamiento, fotogramas por segundo
#define speedSprite 10

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

using namespace std;


void initializeSDL(bool* running){
 if (SDL_Init(SDL_INIT_EVERYTHING) ==
        -1) { //inicializa TIMER, VIDEO, AUDIO, JOISTICK, HAPTIC,GAMECONTROLLER, EVENTS...
        cout<<"There was error initializing SDL: "<< endl
            <<SDL_GetError() << endl;
    }
}

SDL_Window* createWindow(const char* windowName){
    SDL_Window *window = SDL_CreateWindow(windowName,
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     window_width,
                     window_height,
                     SDL_WINDOW_RESIZABLE);


    if(window == NULL){
        cout<<"There was error initializing the window: "<< endl
            <<SDL_GetError() << endl;
    }

    return window;

}

const char * getLastSDLError(){
    return SDL_GetError();
}

SDL_Renderer* createRenderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        cout<<"There was error creating renderer: "<<getLastSDLError()<<endl;
    }
    return renderer;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer,string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());

    if(loadingSurface == NULL)
        cout<<"Error loading surface image for background layer: "<<getLastSDLError()<<endl;

    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        if(backgroundTexture == NULL){
            cout<<"Error creating background layer: "<<getLastSDLError()<<endl;

        }

        SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
        return backgroundTexture;
    }
}

SDL_Texture* createTransparentTexture(SDL_Renderer *renderer){
    return loadTexture(renderer,backgroundTransparentPath);
}

void cap_framerate( Uint32 starting_tick) {
    if ((1000 / fps) > SDL_GetTicks() - starting_tick) {
        SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
    }
}

SDL_Surface* createScreen(SDL_Window* window) {
    SDL_Surface *screen = SDL_GetWindowSurface(window);
    return screen;
}

void setScreenColorBackground(SDL_Surface* screen, Uint32 color){
/*
 *    Uint32 white = SDL_MapRGB( screen->format,255,255,255);
 *    Uint32 red = SDL_MapRGB( screen->format,255,0,0);
 *    Uint32 blue = SDL_MapRGB( screen->format,0,0,255);
 */
    SDL_FillRect( screen, NULL, color);
}

SDL_Surface* createOptimizedSurface(string filePathBMP, SDL_Surface *windowSurface){

    //Optimized image to speed up blitting to surfaces
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface *loadedSurface = SDL_LoadBMP(filePathBMP.c_str());

    if(loadedSurface == NULL){
        cout<<"Error openning image: "<<filePathBMP<<endl<<"Error: "<<getLastSDLError()<<endl;
    }
    else{
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, windowSurface->format,0);
        if(optimizedSurface == NULL){
            cout<<"Error: unable to optimize image: "<<filePathBMP<<endl<<"Error: "<<getLastSDLError()<<endl;
        }
        SDL_FreeSurface(loadedSurface); //Get rid of old loaded surface
        return optimizedSurface;
    }
}

#endif //SDLBASE_SDLTOOLS_H
