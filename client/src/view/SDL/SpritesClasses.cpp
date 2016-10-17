#include "SpritesClasses.h"

Sprite::Sprite(SDL_Texture* layer, SDL_Renderer* mainRenderer, int window_width, int window_height) {

    Sprite::layer = layer;
    Sprite::renderer = mainRenderer;

    Sprite::sourceRect.x = Sprite::sourceRect.y = 0; //FRAME INICIAL
    Sprite::destRect.x = Sprite::destRect.y = 0; //POSICION INICIAL

    Sprite::window_width = window_width;
    Sprite::window_height = window_height;
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
void PlayerSprite::setUpImage(string imageColorPath, string imageGrisadoPath, int wFramesCant, int hFramesCant) {

    Sprite::setUpImage(imageColorPath);

    this->imgaceColorPath = imageColorPath;
    this->imageGrisadoPath = imageGrisadoPath;

    PlayerSprite::wActualPosFrame = 0;

    PlayerSprite::wFramesCant = wFramesCant;
    PlayerSprite::hFramesCant = hFramesCant;

    PlayerSprite::frameWidth = spriteImageWidth / wFramesCant;
    PlayerSprite::frameHeight = spriteImageHeight / hFramesCant;


    PlayerSprite::sourceRect.w = PlayerSprite::frameWidth;
    PlayerSprite::sourceRect.h = PlayerSprite::frameHeight;
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
    if (PlayerSprite::wActualPosFrame == (PlayerSprite::wFramesCant - 1)) {
        PlayerSprite::wActualPosFrame = 0;
    }
    PlayerSprite::sourceRect.x = (PlayerSprite::frameWidth * PlayerSprite::wActualPosFrame);
    PlayerSprite::wActualPosFrame++;
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


void PlayerSprite::handle(struct event nuevoEvento) {

    this->set_position(nuevoEvento.data.x,nuevoEvento.data.y);

    if ((grisado == true) and  (nuevoEvento.data.postura != Postura::DESCONECTADO)) {
        this->colorear();
        grisado = false;
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
            this->grisado = true;
            cout<<" LO VOY A GRISAR AL GIL"<<endl;
            this->grisar();
            break;
        default:
            break;
    }
}

//_______________________________________________________________________________________________________
//BACKGROUNDSPRITE
void BackgroundSprite::setUpImage(string imageSpritePath) {

    Sprite::setUpImage(imageSpritePath);

}

void BackgroundSprite::setFramePosition(int x) {
    int pos = (x + this->frameWidth);
    if (pos == spriteImageWidth){
        //Recorrio toda la imagen
        //TODO: esto es solo para el demo, sacar para la proxima entrega
        printf("llego al limite del background");
        Sprite::sourceRect.x = x-(spriteImageWidth - this->frameWidth);
    }
    else{
        Sprite::sourceRect.x = x;
    }

    //TODO: para la entrega N3 el codigo sera:
//    Sprite::sourceRect.x = x;
}

void BackgroundSprite::handle(struct event nuevoEvento) {
    BackgroundSprite::setFramePosition(nuevoEvento.data.x);
}
