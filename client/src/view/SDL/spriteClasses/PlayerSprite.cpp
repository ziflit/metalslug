#include "PlayerSprite.h"


void PlayerSprite::set_position(int x, int y) {
    Sprite::set_position(x,y);
    this->weaponsDestRect.x = x;
    this->weaponsDestRect.y = y;

}

void PlayerSprite::setWidth(int w) {
    Sprite::setWidth(w);
    this->weaponsDestRect.w = w;
}

void PlayerSprite::setHeight(int h) {
    Sprite::setHeight(h);
    this->weaponsDestRect.h = h;
}

void PlayerSprite::setUpImage(string imageColorPath, string imageGrisadoPath, int wFramesCant, int hFramesCant) {

    Sprite::setUpImage(imageColorPath);

    this->imgaceColorPath = imageColorPath;
    this->imageGrisadoPath = imageGrisadoPath;

    this->wActualPosFrame = 0;

    this->wFramesCant = wFramesCant;

    this->frameWidth = spriteImageWidth / wFramesCant;
    this->frameHeight = spriteImageHeight / hFramesCant;


    this->sourceRect.w = this->frameWidth;
    this->sourceRect.h = this->frameHeight;
}


void PlayerSprite::setUpWeaponsImage(string weaponsPath){
    this->weaponsLayer = loadTexture(renderer,weaponsPath);
    int weaponsImageWidth, weaponsImageHeight;

    SDL_QueryTexture(weaponsLayer,NULL,NULL,&weaponsImageWidth,&weaponsImageHeight);

    weaponsSourceRect.w = this->frameWidth;
    weaponsSourceRect.h = this->frameHeight;
}

void PlayerSprite::actualizarDibujo() {
    if (clientIsConnected()) {
        SDL_RenderCopy(this->renderer,layer,&(this->sourceRect),&(this->destRect));
        if(not grisado){
            SDL_RenderCopy(renderer,weaponsLayer,&(this->weaponsSourceRect),&(this->weaponsDestRect));
        }
        this->usernameText->renderize((this->destRect.x + (frameWidth/2)), (this->destRect.y + (frameHeight + 30) ));
    }

}
void PlayerSprite::colorear() {Sprite::setUpImage(imgaceColorPath);}
void PlayerSprite::grisar() {
    if (!this->grisado){
        this->grisado = true;
        mirandoDerechaQuieto();
        Sprite::setUpImage(imageGrisadoPath);
    }
}

/**  MOVIMIENTOS
*_________________________________________________________________________________________________________
* _________________
*|_____|_____|_____|       - De acuerdo a como este definido el sprite de los player
*|_____|_____|_____|       - se fijaran los valores del frame correspondiente a cada
*|_____|_____|_____|       - uno de los siquientes movimientos, lo que dara la coordenada
*|_____|_____|_____|       - "y" que espera el "PlayerSprite::sourceRect.y".
*/
/** WEAPONS
*_________________________________________________________________________________________________________
* Primera columna: arma a altuna media mirando a derecha
* Segunda columna: arma a altura media mirando a izquierda
* Tercera columna: arma a altura alta mirando a derecha
* Cuarta columna: arma a altura alta mirando a izquierda
* Quinta columna: arma a altura baja mirando a izquierda
* Sexta columna: arma a altura baja mirando a derecha
*   c0    c1    c2    c3    c4    c5         <- Columnas
* ___________________________________
*|_____|_____|_____|_____|_____|_____|       0- PISTOLA
*|_____|_____|_____|_____|_____|_____|       1- HEAVY MACHINE GUN
*|_____|_____|_____|_____|_____|_____|       2- ROCKEY LAUNCHER
*|_____|_____|_____|_____|_____|_____|       3- BOMBA
*|_____|_____|_____|_____|_____|_____|       4- LASER
*|_____|_____|_____|_____|_____|_____|       5- SHOTGUN
*/

void PlayerSprite::setNextSpriteFrame() {
    if(cambioFrame == 2){

        if (this->wActualPosFrame == (this->wFramesCant - 1)) {
            this->wActualPosFrame = 0;
        }
        this->sourceRect.x = (this->frameWidth * this->wActualPosFrame);
        this->wActualPosFrame++;

        cambioFrame = 0;
    } else {
        cambioFrame++;
    }

}

void PlayerSprite::caminandoIzquierda() {
    this->setNextSpriteFrame();
    this->sourceRect.y = 0;
    this->weaponsSourceRect.x = (frameWidth * 1);
}

void PlayerSprite::mirandoArribaCaminandoIzquierda(){
    this->sourceRect.y = (frameHeight * 1);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 3);
}
void PlayerSprite::agachadoMirandoAIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight * 2);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 4);
}
void PlayerSprite::mirandoArribaIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight * 3);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 3);
}
void PlayerSprite::caminandoDerecha(){
    this->sourceRect.y = (frameHeight * 4);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoArribaCaminandoDerecha(){
    this->sourceRect.y = (frameHeight * 5);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 2);
}
void PlayerSprite::agachadoMirandoDerechaQuieto(){
    this->sourceRect.y = (frameHeight * 6);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 5);
}
void PlayerSprite::mirandoArribaDerechaQuieto(){
    this->sourceRect.y = (frameHeight * 7);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 2);
}
void PlayerSprite::agachadoAvanzandoAIzquierda(){
    this->sourceRect.y = (frameHeight * 8);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 4);
}
void PlayerSprite::agachadoAvanzandoADerecha(){
    this->sourceRect.y = (frameHeight * 9);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 5);
}
void PlayerSprite::mirandoDerechaQuieto(){
    this->sourceRect.y = (frameHeight * 10);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight * 11);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth * 1);
}
void PlayerSprite::disparandoDerechaQuieto() {
    this->sourceRect.y = (frameHeight * 12);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoIzquierdaQuieto() {
    this->sourceRect.y = (frameHeight * 13);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoCaminandoDerecha() {
    this->sourceRect.y = (frameHeight * 14);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoCaminandoIzquierda() {
    this->sourceRect.y = (frameHeight * 15);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoMirandoArribaDerechaQuieto() {
    this->sourceRect.y = (frameHeight * 16);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoMirandoArribaIzquierdaQuieto() {
    this->sourceRect.y = (frameHeight * 17);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoAvanzandoMirandoArribaDerecha() {
    this->sourceRect.y = (frameHeight * 18);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::disparandoAvanzandoMirandoArribaIzquierda() {
    this->sourceRect.y = (frameHeight * 19);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::muriendo() {
    this->sourceRect.y = (frameHeight * 20);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::muerto() {
    this->sourceRect.y = (frameHeight * 21);
    this->setNextSpriteFrame();
//    this->weaponsSourceRect.x = frameWidth * 6; //TODO: poner el multiplo correcto cuando esten los sprites de las armas completos.
}
void PlayerSprite::setUsername(struct event nuevoEvento) {
    this->usernameText = new TextBox(nuevoEvento.data.username, this->renderer, {10, 255, 2, 255});
}

void PlayerSprite::handle(struct event nuevoEvento) {
    if (firstEvent()) {
        this->setUsername(nuevoEvento);
    }

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);

    if (grisado and  (nuevoEvento.data.postura != Postura::DESCONECTADO)) {
        this->colorear();
        grisado = false;
    }
    if (this->arma != nuevoEvento.data.arma){
        setWeapon(nuevoEvento.data.arma);
    }
    this->setPostura(nuevoEvento.data.postura);
}

void PlayerSprite::setPostura(Postura postura) {

    switch (postura){
        case Postura::CAMINANDO_IZQUIERDA:
            caminandoIzquierda();
            break;
        case Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA:
            mirandoArribaCaminandoIzquierda();
            break;
        case Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO:
            agachadoMirandoAIzquierdaQuieto();
            break;
        case Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
            mirandoArribaIzquierdaQuieto();
            break;
        case Postura::CAMINANDO_DERECHA:
            caminandoDerecha();
            break;
        case Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA:
            mirandoArribaCaminandoDerecha();
            break;
        case Postura::AGACHADO_MIRANDO_DERECHA_QUIETO:
            agachadoMirandoDerechaQuieto();
            break;
        case Postura::MIRANDO_ARRIBA_DERECHA_QUIETO:
            mirandoArribaDerechaQuieto();
            break;
        case Postura::AGACHADO_AVANZANDO_IZQUIERDA:
            agachadoAvanzandoAIzquierda();
            break;
        case AGACHADO_AVANZANDO_DERECHA:
            agachadoAvanzandoADerecha();
            break;
        case Postura::MIRANDO_DERECHA_QUIETO:
            mirandoDerechaQuieto();
            break;
        case Postura::MIRANDO_IZQUIERDA_QUIETO:
            mirandoIzquierdaQuieto();
            break;
        case Postura::DISPARANDO_DERECHA_QUIETO:
            disparandoDerechaQuieto();
            break;
        case Postura::DISPARANDO_IZQUIERDA_QUIETO:
            disparandoIzquierdaQuieto();
            break;
        case Postura::DISPARANDO_CAMINANDO_DERECHA:
            disparandoCaminandoDerecha();
            break;
        case Postura::DISPARANDO_CAMINANDO_IZQUIERDA:
            disparandoCaminandoIzquierda();
            break;
        case Postura::DISPARANDO_MIRANDO_ARRIBA_DERECHA_QUIETO:
            disparandoMirandoArribaDerechaQuieto();
            break;
        case Postura::DISPARANDO_MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
            disparandoMirandoArribaIzquierdaQuieto();
            break;
        case Postura::DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_DERECHA:
            disparandoAvanzandoMirandoArribaDerecha();
            break;
        case Postura::DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_IZQUIERDA:
            disparandoAvanzandoMirandoArribaIzquierda();
            break;
        case Postura::MURIENDO:
            muriendo();
            break;
        case Postura::MUERTO:
            muerto();
            break;
        case Postura::DESCONECTADO:
            grisar();
            break;
        default:
            break;
    }
}

void PlayerSprite::setWeapon(Arma weapon) {
    this->arma = weapon;

    switch (arma) {
        case PISTOLA:
            this->weaponsSourceRect.y = 0;
            break;
        case HEAVY_MACHINEGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 1 );
//            Sound *heavyMachineSound = new Sound("heaveMachineSound.wav"); //todo
//            heavyMachineSound->playOnce();
//            delete heavyMachineSound;
            break;
        case ROCKET_LAUNCHER:
            this->weaponsSourceRect.y = (this->frameHeight * 2 );
            break;
        case ENEMY_CHASER:
            this->weaponsSourceRect.y = (this->frameHeight * 3 );
            break;
        case SHOTGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 4 );
            break;
        case BOMB:
            this->weaponsSourceRect.y = (this->frameHeight * 5 );
            break;
        default:
            break;
    }
}

PlayerSprite::~PlayerSprite() {
    SDL_DestroyTexture(this->weaponsLayer);
    this->weaponsLayer = nullptr;
}

bool PlayerSprite::firstEvent() {
    return (this->usernameText == nullptr);
}

bool PlayerSprite::clientIsConnected() {
    return (this->usernameText != nullptr);
}
