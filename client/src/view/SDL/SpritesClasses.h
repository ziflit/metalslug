#ifndef SDLBASE_SPRITE_H
#define SDLBASE_SPRITE_H



using namespace std;
#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "../../utils/Protocol.h"

class Sprite {
protected:
    SDL_Rect sourceRect; //rect donde se dibuja el sprite
    SDL_Rect destRect;   //rect donde se hospeda el sprite anterior, este define la pos y tamanio

    SDL_Texture* layer;
    SDL_Renderer* renderer;

    int spriteImageWidth,spriteImageHeight;

    int frameWidth, frameHeight, window_height, window_width;

public:
    //CONSTRUCTOR
    Sprite(SDL_Texture *layer, SDL_Renderer *renderer, int window_width, int window_height);
    SDL_Texture* loadTexture(SDL_Renderer* renderer,string imageTexturePath);
    void setUpImage(string imageSpritePath);
//_________________________________________________________________________________________________________
    //ACTUALIZACION DEL SPRITE
    void handle(struct event nuevoEvento);
    void actualizarDibujo();
//_________________________________________________________________________________________________________
    //TAMANO DEL SPRITE:
    void setWidth(int w){ Sprite::destRect.w = w;}
    void setHeight(int h){ Sprite::destRect.h = h;}
    int getSpriteImageWidth(){ return spriteImageWidth;}
    int getSpriteImageHeight(){return spriteImageHeight;}
//_________________________________________________________________________________________________________
    //POSICION DEL SPRITE:
    void set_position(int x, int y);
    int getXPosition(){ return Sprite::destRect.x;}
    int getYPosition(){ return Sprite::destRect.y;}
//________________________________________________________________________________________________________

    SDL_Texture* getLayer() const { return layer;}
//_________________________________________________________________________________________________________

};

//______________________________________________________________________________________________
//PLAYERSPRITE
class PlayerSprite : public Sprite{

private:
    int wFramesCant,wActualPosFrame,hFramesCant,cambioFrame;
    string imgaceColorPath,imageGrisadoPath;
    bool grisado;
public:
//_______________________________________________________________________________________________
    //Constructor:

    PlayerSprite(SDL_Texture *texture, SDL_Renderer *renderer, int window_width, int window_height) : Sprite(texture, renderer,window_width,window_height) {
//        TODO: este seteo se hace a partir del XML
        PlayerSprite::setHeight(100);
        PlayerSprite::setWidth(100);
        //DEFAULT POSITION
        PlayerSprite::set_position(10,550);
        mirandoDerechaQuieto();
        grisado = false;
        cambioFrame = 0;
    }

//________________________________________________________________
    //OVERRIDE FUNCTIONS:

    void setUpImage(string imageSpritePath,string imageGrisadoPath, int wFramesCant, int hFramesCant);

//__________________________________________________________________

    void handle(struct event nuevoEvento);

    void grisar();
    void colorear();

    void setNextSpriteFrame();
    void caminandoIzquierda();
    void mirandoArribaCaminandoIzquierda();
    void agachadoMirandoAIzquierdaQuieto();
    void mirandoArribaIzquierdaQuieto();
    void caminandoDerecha();
    void mirandoArribaCaminandoDerecha();
    void agachadoMirandoDerechaQuieto();
    void mirandoArribaDerechaQuieto();
    void agachadoAvanzandoAIzquierda();
    void agachadoAvanzandoADerecha();
    void mirandoDerechaQuieto();
    void mirandoIzquierdaQuieto();

    void disparandoDerechaQuieto();
    void disparandoIzquierdaQuieto();
    void disparandoCaminandoDerecha();
    void disparandoCaminandoIzquierda();
    void disparandoAgachadoQuietoDerecha();
    void disparandoAgachadoQuietoIzquierda();
    void disparandoAgachadoAvanzandoDerecha();
    void disparandoAgachadoAvanzandoIzquierda();
    void disparandoMirandoArribaDerechaQuieto();
    void disparandoMirandoParaArribaIzquierdaQuieto();
    void disparandoAvanzandoMirandoArribaDerecha();
    void disparandoAvanzandoMirandoArribaIzquierda();
};

class BackgroundSprite : public Sprite{
private:

public:
    BackgroundSprite(SDL_Texture* texture, SDL_Renderer* renderer, int window_width,int window_height) :
            Sprite(texture, renderer,window_width,window_height) {

        BackgroundSprite::set_position(0,0);
        BackgroundSprite::frameWidth = window_width;
        BackgroundSprite::frameHeight = window_height;

        BackgroundSprite::setWidth(window_width);
        BackgroundSprite::setHeight(window_height);

        BackgroundSprite::sourceRect.w = window_width;
        BackgroundSprite::sourceRect.h = window_height;
    }

    void setUpImage(string imageSpritePath);

    void handle(struct event nuevoEvento);

    void setFramePosition(int x);

    void setNextStartBackFrame();

    void setSourceRectWidth(int w){sourceRect.w = w;}
    void setSourceRectHeight(int h){sourceRect.h = h;}
};

//_______________________________________________________________________________________________

class Marco : public PlayerSprite {
public:
    Marco(SDL_Texture *texture,SDL_Renderer *renderer, int window_width, int window_height, string pathColor) : PlayerSprite(texture,renderer,window_width,window_height) {
        PlayerSprite::setUpImage(pathColor,"sprites/player/marcoGrisado.png",15,12);
    }
};

class Tarma : public PlayerSprite{
public:
    Tarma(SDL_Texture *texture, SDL_Renderer *renderer, int window_width, int window_height, string pathColor) : PlayerSprite(texture,renderer,window_width,window_height){
        PlayerSprite::setUpImage(pathColor,"sprites/player/tarmaGrisado.png",15,12);
    }
};

class Fio : public PlayerSprite{
public:
    Fio(SDL_Texture *texture, SDL_Renderer *renderer, int window_width, int window_height, string pathColor) : PlayerSprite(texture,renderer,window_width,window_height){
        PlayerSprite::setUpImage(pathColor,"sprites/player/fioGrisado.png",15,12);
    }
};

class Eri : public PlayerSprite{
public:
    Eri(SDL_Texture *texture, SDL_Renderer *renderer, int window_width, int window_height, string pathColor) : PlayerSprite(texture, renderer,window_width, window_height){
        PlayerSprite::setUpImage(pathColor,"sprites/player/eriGrisado.png",15,12);
    }
};




#endif //SDLBASE_SPRITE_H
