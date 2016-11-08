#ifndef METALSLUG_PLAYERSPRITE_H
#define METALSLUG_PLAYERSPRITE_H

#include "Sprite.h"
#include "TextBox.h"
#include <SDL2/SDL_ttf.h>

class PlayerSprite : public Sprite{

private:
    SDL_Rect weaponsSourceRect, weaponsDestRect;
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

    void actualizarDibujo();

    void set_position(int x, int y);

    void setWidth(int w);

    void setHeight(int h);

    void setUpImage(string imageSpritePath,string imageGrisadoPath,
                    int wFramesCant, int hFramesCant);
    void setWeapon(Arma weapon);

    void setUpWeaponsImage(string weaponsPath);

    void setPostura(Postura postura);

    void handle(struct event nuevoEvento);

    void clientConected(struct event nuevoEvento);

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
    void disparandoMirandoArribaIzquierdaQuieto();
    void disparandoAvanzandoMirandoArribaDerecha();
    void disparandoAvanzandoMirandoArribaIzquierda();
    void muriendo();
    void muerto();

    virtual ~PlayerSprite();
};

#endif //METALSLUG_PLAYERSPRITE_H
