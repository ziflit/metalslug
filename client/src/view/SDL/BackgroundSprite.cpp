//
// Created by mfprado on 27/09/16.
//

#include "BackgroundSprite.h"

void BackgroundSprite::setUpImage(string imageSpritePath) {

    Sprite::setUpImage(imageSpritePath);

    frameWidth = window_width;
    frameHeight = window_height;

    BackgroundSprite::setWidth(window_width);
    BackgroundSprite::setHeight(window_height);

    BackgroundSprite::sourceRect.w = frameWidth;
    BackgroundSprite::sourceRect.h = frameHeight;
}

void BackgroundSprite::setNextSpriteFrame() {
    //Solo desplazamiento horizontal del frame en direccion ->.
    //Si el jugador principal esta en la mitad de la ventana y hace un paso a la derecha
    //Solo ahi se debe actualizar

    if((BackgroundSprite::spriteImageWidthPanned + window_width) >= Sprite::spriteImageWidth){
        //Recorrio toda la imagen
        printf("llego al limite del background");
        Sprite::sourceRect.x = 0;
        BackgroundSprite::spriteImageWidthPanned=0;
    }
    else{
        BackgroundSprite::spriteImageWidthPanned += speedSprite;
        Sprite::sourceRect.x += speedSprite;   //Avanzo el paneo del frame
    }


}

