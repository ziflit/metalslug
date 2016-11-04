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

void PlayerSprite::actualizarDibujo() {
    if (dibujar) {
        SDL_RenderCopy(this->renderer,layer,&(this->sourceRect),&(this->destRect));
        SDL_RenderCopy(renderer,weaponsLayer,&(this->weaponsSourceRect),&(this->weaponsDestRect));
        this->usernameText->renderize((this->destRect.x + (frameWidth/2)), (this->destRect.y + (frameHeight + 30) ));
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

void PlayerSprite::setWeapon(Arma weapon) {
    this->arma = weapon;

    switch (arma) {
        case PISTOLA:
            this->weaponsSourceRect.y = 0;
        case HEAVY_MACHINEGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 1 );
        case ROCKET_LAUNCHER:
            this->weaponsSourceRect.y = (this->frameHeight * 2 );
        case ENEMY_CHASER:
            this->weaponsSourceRect.y = (this->frameHeight * 3 );
        case SHOTGUN:
            this->weaponsSourceRect.y = (this->frameHeight * 4 );
        case BOMB:
            this->weaponsSourceRect.y = (this->frameHeight * 5 );
    }
}

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

void PlayerSprite::clientConected(struct event nuevoEvento) {
    this->dibujar = true;
    stpcpy(this->username , nuevoEvento.data.username);
    this->usernameText = new TextBox(this->username, this->renderer, {10, 255, 2, 255});
}


void PlayerSprite::handle(struct event nuevoEvento) {
    if (not dibujar) {
        this->clientConected(nuevoEvento);
    }

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

void EnemySprite::setWidth(int w) {
    Sprite::setWidth(w);
    this->weaponsDestRect.w = w;
}

void EnemySprite::setHeight(int h) {
    Sprite::setHeight(h);
    this->weaponsDestRect.h = h;
}

void EnemySprite::setUpImage(string imageColorPath, string imageGrisadoPath, int wFramesCant, int hFramesCant) {

    this->dibujar = false;

    Sprite::setUpImage(imageColorPath);

    this->imgaceColorPath = imageColorPath;
    this->imageGrisadoPath = imageGrisadoPath;

    EnemySprite::wActualPosFrame = 0;

    EnemySprite::wFramesCant = wFramesCant;
    EnemySprite::hFramesCant = hFramesCant;

    EnemySprite::frameWidth = spriteImageWidth / wFramesCant;
    EnemySprite::frameHeight = spriteImageHeight / hFramesCant;


    EnemySprite::sourceRect.w = EnemySprite::frameWidth;
    EnemySprite::sourceRect.h = EnemySprite::frameHeight;
}

void EnemySprite::setUpWeaponsImage(string weaponsPath){
    this->weaponsLayer = loadTexture(renderer,weaponsPath);
    int weaponsImageWidth, weaponsImageHeight;

    SDL_QueryTexture(weaponsLayer,NULL,NULL,&weaponsImageWidth,&weaponsImageHeight);

    weaponsSourceRect.w = this->frameWidth;
    weaponsSourceRect.h = this->frameHeight;
}

void EnemySprite::setWeapon(Arma weapon) {
    this->arma = arma;

//TODO:cuando esten los sprites aqui se setea la fila correspondiente
    switch (arma) {
        case PISTOLA:
            EnemySprite::weaponsSourceRect.y = 0;
        case HEAVY_MACHINEGUN:
            EnemySprite::weaponsSourceRect.y = (EnemySprite::frameHeight * 1 );
        case ROCKET_LAUNCHER:
            EnemySprite::weaponsSourceRect.y = (EnemySprite::frameHeight * 2 );
        case ENEMY_CHASER:
            EnemySprite::weaponsSourceRect.y = (EnemySprite::frameHeight * 3 );
        case SHOTGUN:
            EnemySprite::weaponsSourceRect.y = (EnemySprite::frameHeight * 4 );
        case BOMB:
            EnemySprite::weaponsSourceRect.y = (EnemySprite::frameHeight * 5 );
    }
}

void EnemySprite::colorear() {Sprite::setUpImage(imgaceColorPath);}
void EnemySprite::grisar() {Sprite::setUpImage(imgaceColorPath);}

/**  MOVIMIENTOS
*_________________________________________________________________________________________________________
* _________________
*|_____|_____|_____|       - De acuerdo a como este definido el sprite de los player
*|_____|_____|_____|       - se fijaran los valores del frame correspondiente a cada
*|_____|_____|_____|       - uno de los siquientes movimientos, lo que dara la coordenada
*|_____|_____|_____|       - "y" que espera el "EnemySprite::sourceRect.y".
*/

void EnemySprite::setNextSpriteFrame() {
    if(cambioFrame == 2){

        if (EnemySprite::wActualPosFrame == (EnemySprite::wFramesCant - 1)) {
            EnemySprite::wActualPosFrame = 0;
        }
        EnemySprite::sourceRect.x = (EnemySprite::frameWidth * EnemySprite::wActualPosFrame);
        EnemySprite::wActualPosFrame++;

        cambioFrame = 0;
    } else {
        cambioFrame++;
    }

}
//TODO: setear el arma.
void EnemySprite::caminandoIzquierda() {
    EnemySprite::setNextSpriteFrame();
    EnemySprite::sourceRect.y = 0;
    EnemySprite::weaponsSourceRect.x = EnemySprite::frameWidth * 1;
}
void EnemySprite::mirandoArribaCaminandoIzquierda(){
    EnemySprite::sourceRect.y = (frameHeight*1);
    EnemySprite::setNextSpriteFrame();
//    EnemySprite::weaponsSourceRect.x = EnemySprite::frameWidth * 3;
}
void EnemySprite::agachadoMirandoAIzquierdaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*2);
    EnemySprite::setNextSpriteFrame();
//    EnemySprite::weaponsSourceRect.x = EnemySprite::frameWidth * 1;
}
void EnemySprite::mirandoArribaIzquierdaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*3);
    EnemySprite::setNextSpriteFrame();
//    EnemySprite::weaponsSourceRect.x = EnemySprite::frameWidth * 1;
}
void EnemySprite::caminandoDerecha(){
    EnemySprite::sourceRect.y = (frameHeight*4);
    EnemySprite::setNextSpriteFrame();
//    EnemySprite::weaponsSourceRect.x = 0;
}
void EnemySprite::mirandoArribaCaminandoDerecha(){
    EnemySprite::sourceRect.y = (frameHeight*5);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::agachadoMirandoDerechaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*6);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::mirandoArribaDerechaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*7);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::agachadoAvanzandoAIzquierda(){
    EnemySprite::sourceRect.y = (frameHeight*8);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::agachadoAvanzandoADerecha(){
    EnemySprite::sourceRect.y = (frameHeight*9);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::mirandoDerechaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*10);
    EnemySprite::setNextSpriteFrame();
}
void EnemySprite::mirandoIzquierdaQuieto(){
    EnemySprite::sourceRect.y = (frameHeight*11);
    EnemySprite::setNextSpriteFrame();
}


void EnemySprite::handle(struct event nuevoEvento) {
    this->dibujar = true;

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

PlayerSprite::~PlayerSprite() {
    SDL_DestroyTexture(this->weaponsLayer);
    this->weaponsLayer = nullptr;
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