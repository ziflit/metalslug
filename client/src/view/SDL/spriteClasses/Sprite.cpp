#include "Sprite.h"
Sprite::Sprite(SDL_Renderer* mainRenderer) {

    this->renderer = mainRenderer;

    this->sourceRect.x = this->sourceRect.y = 0; //FRAME INICIAL
    this->destRect.x = this->destRect.y = 0; //POSICION INICIAL
}

SDL_Texture* Sprite::loadTexture(string imageTexturePath){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());
    if(loadingSurface == NULL){
        cout<<"Error: can't load image which path is: "<<imageTexturePath.c_str()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }


    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

    if(backgroundTexture == NULL) cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}

void Sprite::setUpImage(string imageSpritePath) {
    this->layer = loadTexture(imageSpritePath);
    SDL_QueryTexture(layer,NULL, NULL,&spriteImageWidth,&spriteImageHeight);
}

void Sprite::actualizarDibujo(){
    SDL_RenderCopy(renderer,layer,&(this->sourceRect),&(this->destRect));
}

void Sprite::set_position(int x, int y) {
    this->destRect.x = x;
    this->destRect.y = y;
}