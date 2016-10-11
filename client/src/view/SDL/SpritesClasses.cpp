#include "SpritesClasses.h"

Sprite::Sprite(SDL_Texture *layer, SDL_Renderer *mainRenderer) {

    Sprite::layer = layer;
    Sprite::renderer = mainRenderer;

    Sprite::sourceRect.x = Sprite::sourceRect.y = 0; //FRAME INICIAL
    Sprite::destRect.x = Sprite::destRect.y = 0; //POSICION INICIAL

    Sprite::window_width = 800;
    Sprite::window_height = 600;
}

void Sprite::setUpImage(string imageSpritePath) {
    layer = loadTexture(renderer,imageSpritePath);
    SDL_QueryTexture(layer,NULL,NULL,&spriteImageWidth,&spriteImageHeight);
}

void Sprite::actualizarDibujo(){   //COPIA EN LA CAPA DEL PLAYER EL NUEVO ESTADO DEL SPRITE
    SDL_RenderCopy(renderer,layer,&(Sprite::sourceRect),&(Sprite::destRect));
}

void Sprite::set_position(int x, int y) {
    Sprite::destRect.x = x;
    Sprite::destRect.y = y;
}

SDL_Texture* Sprite::loadTexture(SDL_Renderer* renderer,string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());

    if(loadingSurface == NULL)
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;

    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        if(backgroundTexture == NULL){
            cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

        }

        SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
        return backgroundTexture;
    }
}

//________________________________________________________________________________________________________
//PLAYER SPRITE
void PlayerSprite::setUpImage(string imageSpritePath, int wFramesCant, int hFramesCant) {

    Sprite::setUpImage(imageSpritePath);

    PlayerSprite::wActualPosFrame = 0;

    PlayerSprite::wFramesCant = wFramesCant;

    PlayerSprite::frameWidth = spriteImageWidth / wFramesCant;
    PlayerSprite::frameHeight = spriteImageHeight / hFramesCant;

    PlayerSprite::sourceRect.w = PlayerSprite::frameWidth;
    PlayerSprite::sourceRect.h = PlayerSprite::frameHeight;
}

//  MOVIMIENTOS
//_________________________________________________________________________________________________________
// _________________
//|_____|_____|_____|       - De acuerdo a como este definido el sprite de los player
//|_____|_____|_____|       - se fijaran los valores del frame correspondiente a cada
//|_____|_____|_____|       - uno de los siquientes movimientos, lo que dara la coordenada
//|_____|_____|_____|       - "y" que espera el "PlayerSprite::sourceRect.y".
//

void PlayerSprite::handle(struct event nuevoEvento) {

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);
    //TODO: FALTA MANEJAR ACA EL CAMBIO DE FRAMES.
}

void PlayerSprite::caminandoIzquierda() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = 0;
}
void PlayerSprite::mirandoArribaCaminandoIzquierda(){
    PlayerSprite::sourceRect.y = (frameHeight*1);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::agachadoMirandoAIzquierdaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*2);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::mirandoArribaIzquierdaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*3);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::caminandoDerecha(){
    PlayerSprite::sourceRect.y = (frameHeight*4);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::mirandoArribaCaminandoDerecha(){
    PlayerSprite::sourceRect.y = (frameHeight*5);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::agachadoMirandoDerechaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*6);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::mirandoArribaDerechaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*7);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::agachadoAvanzandoAIzquierda(){
    PlayerSprite::sourceRect.y = (frameHeight*8);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::agachadoAvanzandoADerecha(){
    PlayerSprite::sourceRect.y = (frameHeight*9);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::mirandoDerechaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*10);
    PlayerSprite::setNextSpriteFrame();
}
void PlayerSprite::mirandoIzquierdaQuieto(){
    PlayerSprite::sourceRect.y = (frameHeight*11);
    PlayerSprite::setNextSpriteFrame();
}

void PlayerSprite::setNextSpriteFrame() {
    if (PlayerSprite::wActualPosFrame == (PlayerSprite::wFramesCant - 1)) {
        PlayerSprite::wActualPosFrame = 0;
    }
    PlayerSprite::sourceRect.x = (PlayerSprite::frameWidth * PlayerSprite::wActualPosFrame);
    PlayerSprite::wActualPosFrame++;
}

//_______________________________________________________________________________________________________
//BACKGROUNDSPRITE
void BackgroundSprite::setUpImage(string imageSpritePath) {

    Sprite::setUpImage(imageSpritePath);

    frameWidth = BackgroundSprite::window_width;
    frameHeight = BackgroundSprite::window_height;

    BackgroundSprite::setWidth(window_width);
    BackgroundSprite::setHeight(window_height);

    BackgroundSprite::sourceRect.w = BackgroundSprite::frameWidth;
    BackgroundSprite::sourceRect.h = BackgroundSprite::frameHeight;
}

void BackgroundSprite::setFramePosition(int x) {

    if (((x - (this->spriteImageWidthPanned*Sprite::spriteImageWidth)) + frameWidth) >= Sprite::spriteImageWidth){
        //Recorrio toda la imagen
        //TODO: esto es solo para el demo, sacar para la proxima entrega
        printf("llego al limite del background");
        Sprite::sourceRect.x = 0;
        this->spriteImageWidthPanned += 1;
    }
    else if(spriteImageWidthPanned>0){
        Sprite::sourceRect.x = x - (this->spriteImageWidthPanned*Sprite::spriteImageWidth);
    }
    else{
        Sprite::sourceRect.x = x;
    }

    //TODO: para la entrega N3 el codigo sera:
    //Sprite::sourceRect.x = x;
}

void BackgroundSprite::handle(struct event nuevoEvento) {
    BackgroundSprite::setFramePosition(nuevoEvento.data.x);
}



