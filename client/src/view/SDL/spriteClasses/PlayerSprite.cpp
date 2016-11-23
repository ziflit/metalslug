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

void PlayerSprite::setUpImage(string imageColorPath, string imageGrisadoPath) {

    Sprite::setUpImage(imageColorPath);

    this->imgaceColorPath = imageColorPath;
    this->imageGrisadoPath = imageGrisadoPath;

    this->wActualPosFrame = 0;
}


void PlayerSprite::setUpWeaponsImage(string weaponsPath){
    this->weaponsLayer = loadTexture(weaponsPath);
    weaponsSourceRect.w = sourceRect.w;
    weaponsSourceRect.h = sourceRect.h;
    weaponsSourceRect.x = weaponsSourceRect.y = 0;
    weaponsDestRect.x = weaponsDestRect.y = 0;
}

void PlayerSprite::actualizarDibujo() {
    if (clientIsConnected()) {
        SDL_RenderCopy(this->renderer,layer,&(this->sourceRect),&(this->destRect));
        if (not ((postura==DESCONECTADO)) or (postura==MURIENDO) or (postura==MUERTO)) {
            SDL_RenderCopy(renderer,weaponsLayer,&(this->weaponsSourceRect),&(this->weaponsDestRect));
        }
        this->usernameText->renderize((this->destRect.x + (sourceRect.w/2)), (this->destRect.y + (sourceRect.h *2) ));
        this->bar->actualizarDibujo();
    }

}
void PlayerSprite::colorear() {Sprite::setUpImage(imgaceColorPath);}
void PlayerSprite::grisar() {
    if (postura != DESCONECTADO){
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
        this->sourceRect.x = (this->sourceRect.w * this->wActualPosFrame);
        this->wActualPosFrame++;

        cambioFrame = 0;
    } else {
        cambioFrame++;
    }

}

void PlayerSprite::caminandoIzquierda() {
    this->setNextSpriteFrame();
    this->sourceRect.y = 0;
    this->weaponsSourceRect.x = (this->sourceRect.w * 1);
}
void PlayerSprite::mirandoArribaCaminandoIzquierda(){
    this->sourceRect.y = (sourceRect.h * 1);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 2);
}
void PlayerSprite::agachadoMirandoAIzquierdaQuieto(){
    this->sourceRect.y = (sourceRect.h * 2);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 4);
}
void PlayerSprite::mirandoArribaIzquierdaQuieto(){
    this->sourceRect.y = (sourceRect.h * 3);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 2);
}
void PlayerSprite::caminandoDerecha(){
    this->sourceRect.y = (sourceRect.h * 4);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoArribaCaminandoDerecha(){
    this->sourceRect.y = (sourceRect.h * 5);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 3);
}
void PlayerSprite::agachadoMirandoDerechaQuieto(){
    this->sourceRect.y = (sourceRect.h * 6);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 5);
}
void PlayerSprite::mirandoArribaDerechaQuieto(){
    this->sourceRect.y = (sourceRect.h * 7);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 3);
}
void PlayerSprite::agachadoAvanzandoAIzquierda(){
    this->sourceRect.y = (sourceRect.h * 8);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 4);
}
void PlayerSprite::agachadoAvanzandoADerecha(){
    this->sourceRect.y = (sourceRect.h * 9);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 5);
}
void PlayerSprite::mirandoDerechaQuieto(){
    this->sourceRect.y = (sourceRect.h * 10);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoIzquierdaQuieto(){
    this->sourceRect.y = (sourceRect.h * 11);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 1);
}
void PlayerSprite::disparandoDerechaQuieto() {
    this->sourceRect.y = (sourceRect.h * 12);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 8);
}
void PlayerSprite::disparandoIzquierdaQuieto() {
    this->sourceRect.y = (sourceRect.h * 13);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 9);
}
void PlayerSprite::disparandoCaminandoDerecha() {
    this->sourceRect.y = (sourceRect.h * 14);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 8);
}
void PlayerSprite::disparandoCaminandoIzquierda() {
    this->sourceRect.y = (sourceRect.h * 15);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 9);
}
void PlayerSprite::disparandoAgachadoQuietoDerecha() {
    this->sourceRect.y = (sourceRect.h * 16);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 7);
}
void PlayerSprite::disparandoAgachadoQuietoIzquierda() {
    this->sourceRect.y = (sourceRect.h * 17);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 6);
}
void PlayerSprite::disparandoMirandoArribaDerechaQuieto() {
    this->sourceRect.y = (sourceRect.h * 18);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 3);
}
void PlayerSprite::disparandoMirandoArribaIzquierdaQuieto() {
    this->sourceRect.y = (sourceRect.h * 19);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 2);
}
void PlayerSprite::disparandoAvanzandoMirandoArribaDerecha() {
    this->sourceRect.y = (sourceRect.h * 20);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 3);
}
void PlayerSprite::disparandoAvanzandoMirandoArribaIzquierda() {
    this->sourceRect.y = (sourceRect.h * 21);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 2);
}
void PlayerSprite::muriendo() {
    this->sourceRect.y = (sourceRect.h * 23);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (sourceRect.w * 100);
}
void PlayerSprite::setUsername(struct event nuevoEvento) {
    strncpy(username, nuevoEvento.data.username, 20);
    this->usernameText = new TextBox(nuevoEvento.data.username, this->renderer, {3,255,0,1},12);
}

void PlayerSprite::handle(struct event nuevoEvento) {
    if (firstEvent()) this->setUsername(nuevoEvento);
    if ((postura == DESCONECTADO) and  (nuevoEvento.data.postura != Postura::DESCONECTADO)) this->colorear();
    if (this->arma != nuevoEvento.data.arma) setWeapon(nuevoEvento.data.arma);
    this->puntaje = nuevoEvento.data.puntaje;
    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);
    this->setPostura(nuevoEvento.data.postura);
    this->updateHealthText(nuevoEvento.data.health);
    this->bar->updateScore(nuevoEvento.data.puntaje);
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
        case Postura::DISPARANDO_AGACHADO_QUIETO_DERECHA:
            disparandoAgachadoQuietoDerecha();
            break;
        case Postura::DISPARANDO_AGACHADO_QUIETO_IZQUIERDA:
            disparandoAgachadoQuietoIzquierda();
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
        case Postura::DESCONECTADO:
            grisar();
            break;
        default:
            break;
    }
    this->postura = postura;
}

void PlayerSprite::setWeapon(Entity weapon) {
    this->arma = weapon;

    switch (arma) {
        case BT_BULLET:
            this->weaponsSourceRect.y = 0;
            break;
        case BT_HEAVY_BULLET:
            this->weaponsSourceRect.y = (this->sourceRect.h * 1 );
            this->playHeavyMachineGunSound();
            break;
        case BT_MISSILE:
            this->weaponsSourceRect.y = (this->sourceRect.h * 2 );
            break;
        case BT_TELE_MISSILE:
            this->weaponsSourceRect.y = (this->sourceRect.h * 3 );
            break;
        case BT_SHOT:
            this->weaponsSourceRect.y = (this->sourceRect.h * 4 );
            break;
        case BT_BOMB:
            this->weaponsSourceRect.y = (this->sourceRect.h * 5 );
            break;
        default:
            break;
    }
}

void PlayerSprite::playHeavyMachineGunSound() {

    Sound *heavyMachineSound = new Sound(heavySound);
    heavyMachineSound->playOnce();
    delete heavyMachineSound;
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

void PlayerSprite::updateHealthText(int health) {
    if(health == 999999) {
        if(firstEvent()){
            this->bar->updateHealth("---");
        }
        return;
    }
    if (not ((postura == MURIENDO) or (postura == MUERTO))) this->bar->updateHealth(health);
    else this->bar->updateHealth(0);
}

SDL_Renderer *PlayerSprite::getRenderer() {
    return this->renderer;
}

int PlayerSprite::getPuntaje() {
    return puntaje;
}
char *PlayerSprite::getUsername()  {
    return username;
}
