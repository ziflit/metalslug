#include "Sprite.h"
Sprite::Sprite(SDL_Renderer* mainRenderer, int window_width, int window_height) {

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
}