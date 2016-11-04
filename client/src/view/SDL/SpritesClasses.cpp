#include "SpritesClasses.h"

Sprite::Sprite(SDL_Renderer* mainRenderer, int window_width, int window_height) {

    this->layer = layer;
    this->renderer = mainRenderer;

    this->sourceRect.x = this->sourceRect.y = 0; //FRAME INICIAL
    this->destRect.x = this->destRect.y = 0; //POSICION INICIAL

    this->window_width = window_width;
    this->window_height = window_height;
}

SDL_Texture* Sprite::loadTexture(SDL_Renderer* renderer,string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());

    if(loadingSurface == NULL){
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

    if(backgroundTexture == NULL){
        cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

    }

    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}


void Sprite::setUpImage(string imageSpritePath) {
    this->layer = loadTexture(renderer,imageSpritePath);
    SDL_QueryTexture(layer,NULL, NULL,&spriteImageWidth,&spriteImageHeight);
}

void Sprite::actualizarDibujo(){
    SDL_RenderCopy(renderer,layer,&(this->sourceRect),&(this->destRect));
}

void Sprite::set_position(int x, int y) {
    this->destRect.x = x;
    this->destRect.y = y;
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

    this->dibujar = false;

    Sprite::setUpImage(imageColorPath);

    this->imgaceColorPath = imageColorPath;
    this->imageGrisadoPath = imageGrisadoPath;

    this->wActualPosFrame = 0;

    this->wFramesCant = wFramesCant;
    this->hFramesCant = hFramesCant;

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

void PlayerSprite::setWeapon(Arma weapon) {
    this->arma = weapon;

    switch (arma) {
        case PISTOLA:
            this->weaponsSourceRect.y = 0;
        case HEAVY_MACHINEGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 1 );
        case ROCKET_LAUNCHER:
            this->weaponsSourceRect.y = (this->frameHeight * 2 );
        case BOMBA:
            this->weaponsSourceRect.y = (this->frameHeight * 3 );
        case LASER:
            this->weaponsSourceRect.y = (this->frameHeight * 4 );
        case SHOTGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 5 );
    }
}

void PlayerSprite::colorear() {Sprite::setUpImage(imgaceColorPath);}
void PlayerSprite::grisar() {Sprite::setUpImage(imageGrisadoPath);}

/**  MOVIMIENTOS
*_________________________________________________________________________________________________________
* _________________
*|_____|_____|_____|       - De acuerdo a como este definido el sprite de los player
*|_____|_____|_____|       - se fijaran los valores del frame correspondiente a cada
*|_____|_____|_____|       - uno de los siquientes movimientos, lo que dara la coordenada
*|_____|_____|_____|       - "y" que espera el "PlayerSprite::sourceRect.y".
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
//TODO: setear el arma.
void PlayerSprite::caminandoIzquierda() {
    this->setNextSpriteFrame();
    this->sourceRect.y = 0;
    this->weaponsSourceRect.x = this->frameWidth * 1;
}
void PlayerSprite::mirandoArribaCaminandoIzquierda(){
    this->sourceRect.y = (frameHeight*1);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = this->frameWidth * 3;
}
void PlayerSprite::agachadoMirandoAIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight*2);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = this->frameWidth * 4;
}
void PlayerSprite::mirandoArribaIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight*3);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = this->frameWidth * 3;
}
void PlayerSprite::caminandoDerecha(){
    this->sourceRect.y = (frameHeight*4);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoArribaCaminandoDerecha(){
    this->sourceRect.y = (frameHeight*5);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = frameWidth*2;
}
void PlayerSprite::agachadoMirandoDerechaQuieto(){
    this->sourceRect.y = (frameHeight*6);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = frameWidth*5;
}
void PlayerSprite::mirandoArribaDerechaQuieto(){
    this->sourceRect.y = (frameHeight*7);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = (frameWidth*2);
}
void PlayerSprite::agachadoAvanzandoAIzquierda(){
    this->sourceRect.y = (frameHeight*8);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = frameWidth*4;
}
void PlayerSprite::agachadoAvanzandoADerecha(){
    this->sourceRect.y = (frameHeight*9);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = frameWidth*5;
}
void PlayerSprite::mirandoDerechaQuieto(){
    this->sourceRect.y = (frameHeight*10);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = 0;
}
void PlayerSprite::mirandoIzquierdaQuieto(){
    this->sourceRect.y = (frameHeight*11);
    this->setNextSpriteFrame();
    this->weaponsSourceRect.x = frameWidth * 1;
}


void PlayerSprite::handle(struct event nuevoEvento) {
    this->clientConected();

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);

    if (grisado and  (nuevoEvento.data.postura != Postura::DESCONECTADO)) {
        this->colorear();
        grisado = false;
    }
    if (this->arma != nuevoEvento.data.arma){
        setWeapon(nuevoEvento.data.arma);
    }

    switch (nuevoEvento.data.postura){

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
        case Postura::MIRANDO_IZQUIERDA_QUIETO :
            mirandoIzquierdaQuieto();
            break;
        case Postura::DESCONECTADO:
            if (!this->grisado){
                this->grisado = true;
                mirandoDerechaQuieto();
                this->grisar();
            }
            break;
        default:
            break;
    }
}

void BackgroundSprite::setUpImage(string imageSpritePath) {

    Sprite::setUpImage(imageSpritePath);

}

void BackgroundSprite::setFramePosition(int x) {
        Sprite::sourceRect.x = x;
}

void BackgroundSprite::handle(struct event nuevoEvento) {
    BackgroundSprite::setFramePosition(nuevoEvento.data.x);
}

void BackgroundSprite::setNextStartBackFrame(){
    if(Sprite::sourceRect.x == 0){
        Sprite::sourceRect.x = spriteImageWidth / 2;
    }
    else{
        Sprite::sourceRect.x = 0;
    }
}