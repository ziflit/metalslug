#ifndef METALSLUG_PLAYERSPRITE_H
#define METALSLUG_PLAYERSPRITE_H

#include "Sprite.h"
#include "../sound-ttf/Sound.h"
#include "../sound-ttf/TextBox.h"
#include <SDL2/SDL_ttf.h>

class PlayerSprite : public Sprite{

private:
    SDL_Rect weaponsSourceRect, weaponsDestRect;
    SDL_Texture* weaponsLayer;
    TextBox* usernameText;
    Arma arma;
    int groupId;
    int wFramesCant,wActualPosFrame,cambioFrame;
    Postura postura;
    string imgaceColorPath,imageGrisadoPath;
public:

    PlayerSprite(SDL_Renderer *renderer, xmlPlayer playerConfig) : Sprite(renderer) {
        postura = CAMINANDO_DERECHA;
        cambioFrame = 0;
        this->setWidth(playerConfig.ancho);
        this->setHeight(playerConfig.alto);
        this->setId(playerConfig.id);
        wFramesCant = playerConfig.cantWidthFrames;
        setUpImage(playerConfig.pathColor, playerConfig.pathGrey);

        sourceRect.w = spriteImageWidth / playerConfig.cantWidthFrames;
        sourceRect.h = spriteImageHeight / playerConfig.cantHeightFrames;

        this->setUpWeaponsImage(playerConfig.pathWeapons);
        this->usernameText = nullptr;
    }

    void actualizarDibujo();

    void set_position(int x, int y);

    void setWidth(int w);

    void setHeight(int h);

    void setUpImage(string imageSpritePath,string imageGrisadoPath);
    void setWeapon(Arma weapon);

    void setUpWeaponsImage(string weaponsPath);

    void setPostura(Postura postura);

    void handle(struct event nuevoEvento);

    void setUsername(struct event nuevoEvento);

    bool firstEvent();

    bool clientIsConnected();

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
    void disparandoMirandoArribaDerechaQuieto();
    void disparandoMirandoArribaIzquierdaQuieto();
    void disparandoAvanzandoMirandoArribaDerecha();
    void disparandoAvanzandoMirandoArribaIzquierda();
    void muriendo();

    virtual ~PlayerSprite();

    void playHeavyMachineGunSound();

    void setGroupId(xmlGameMode mode);
};

#endif //METALSLUG_PLAYERSPRITE_H
