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

