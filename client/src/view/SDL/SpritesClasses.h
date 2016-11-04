#ifndef SDLBASE_SPRITE_H
#define SDLBASE_SPRITE_H



using namespace std;
#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../utils/Protocol.h"
#include "TextBox.h"

class Sprite {
protected:
    SDL_Rect sourceRect, weaponsSourceRect; //rect donde se dibuja el sprite
    SDL_Rect destRect, weaponsDestRect;   //rect donde se hospeda el sprite anterior, este define la pos y tamanio

    SDL_Texture* layer;
    SDL_Renderer* renderer;

    int spriteImageWidth,spriteImageHeight;

    int frameWidth, frameHeight, window_height, window_width;

    Entity id;

public:

    Sprite(SDL_Renderer *renderer, int window_width, int window_height);
    SDL_Texture* loadTexture(SDL_Renderer* renderer,string imageTexturePath);
    void setUpImage(string imageSpritePath);

    void
    handle(struct event nuevoEvento){}
    void actualizarDibujo();

    void setId(Entity id){ this->id = id;}
    Entity getId(){ return id;}

    void setWidth(int w){ Sprite::destRect.w = w;}
    void setHeight(int h){ Sprite::destRect.h = h;}
    int getSpriteImageWidth(){ return spriteImageWidth;}
    int getSpriteImageHeight(){return spriteImageHeight;}

    void set_position(int x, int y);
    int getXPosition(){ return Sprite::destRect.x;}
    int getYPosition(){ return Sprite::destRect.y;}


};

class PlayerSprite : public Sprite{

private:
    char username[20];
    int wFramesCant,hFramesCant,wActualPosFrame,cambioFrame;
    SDL_Texture* weaponsLayer;
    TextBox* usernameText;
    string imgaceColorPath,imageGrisadoPath;
    bool grisado, dibujar;
    Arma arma;
public:

    PlayerSprite(SDL_Renderer *renderer, int window_width, int window_height) : Sprite(renderer,window_width,window_height) {

        PlayerSprite::set_position(5,550);
        mirandoDerechaQuieto();
        setWeapon(PISTOLA);
        grisado = false;
        cambioFrame = 0;
        this->weaponsSourceRect.x = this->weaponsSourceRect.y = 0; //FRAME INICIAL
        this->weaponsDestRect.x = this->weaponsDestRect.y = 0; //POSICION INICIAL
    }

    void setWidth(int w);

    void setHeight(int h);

    void setWeapon(Arma weapon);

    void setUpImage(string imageSpritePath,string imageGrisadoPath,
                    int wFramesCant, int hFramesCant);

    void setUpWeaponsImage(string weaponsPath);

    void handle(struct event nuevoEvento);

    void clientConected(struct event nuevoEvento);

    void actualizarDibujo();

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

    virtual ~PlayerSprite();

};

class EnemySprite : public Sprite{

private:
    int wFramesCant,hFramesCant,wActualPosFrame,cambioFrame;
    SDL_Texture* weaponsLayer;
    string imgaceColorPath,imageGrisadoPath;
    bool grisado, dibujar;
    Arma arma;
public:

    EnemySprite(SDL_Renderer *renderer, int window_width, int window_height) : Sprite(renderer,window_width,window_height) {

        EnemySprite::set_position(5,550);
        mirandoDerechaQuieto();
        setWeapon(PISTOLA);
        grisado = false;
        cambioFrame = 0;
        this->weaponsSourceRect.x = this->weaponsSourceRect.y = 0; //FRAME INICIAL
        this->weaponsDestRect.x = this->weaponsDestRect.y = 0; //POSICION INICIAL
    }

    void setWidth(int w);

    void setHeight(int h);

    void setWeapon(Arma weapon);

    void setUpImage(string imageSpritePath,string imageGrisadoPath,
                    int wFramesCant, int hFramesCant);

    void setUpWeaponsImage(string weaponsPath);

    void handle(struct event nuevoEvento);

    void actualizarDibujo(){
            SDL_RenderCopy(this->renderer,layer,&(this->sourceRect),&(this->destRect));
//            SDL_RenderCopy(renderer,weaponsLayer,&(this->weaponsSourceRect),&(this->weaponsDestRect));
    }

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
    BackgroundSprite(SDL_Renderer* renderer, int window_width,int window_height) :
            Sprite(renderer,window_width,window_height) {

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




#endif //SDLBASE_SPRITE_H
