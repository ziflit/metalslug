#include "Sprite.h"

Sprite::Sprite(SDL_Texture *layer, SDL_Renderer *mainRenderer) {

    Sprite::layer = layer;
    Sprite::renderer = mainRenderer;

    Sprite::sourceRect.x = Sprite::sourceRect.y = 0; //FRAME INICIAL
    Sprite::destRect.x = Sprite::destRect.y = 0; //POSICION INICIAL

    Sprite::frameTime = 0;
}

void Sprite::setUpImage(string imageSpritePath) {
    layer = loadTexture(renderer,imageSpritePath);
    SDL_QueryTexture(layer,NULL,NULL,&spriteImageWidth,&spriteImageHeight);
}

void Sprite::update(){   //COPIA EN LA CAPA DEL PLAYER EL NUEVO ESTADO DEL SPRITE
    SDL_RenderCopy(renderer,layer,&(Sprite::sourceRect),&(Sprite::destRect));
}

void Sprite::set_position(int x, int y) {
    Sprite::destRect.x = x;
    Sprite::destRect.y = y;
}



