//
// Created by mfprado on 27/09/16.
//

#include "BackgroundSprite.h"

void BackgroundSprite::setUpImage(string imageSpritePath) {

    Sprite::setUpImage(imageSpritePath);

    frameWidth = BackgroundSprite::window_width;
    frameHeight = BackgroundSprite::window_height;

    BackgroundSprite::setWidth(window_width);
    BackgroundSprite::setHeight(window_height);

    BackgroundSprite::sourceRect.w = BackgroundSprite::frameWidth;
    BackgroundSprite::sourceRect.h = BackgroundSprite::frameHeight;
}

//void BackgroundSprite::setNextSpriteFrame() {
//    //Solo desplazamiento horizontal del frame en direccion ->.
//    //Si el jugador principal esta en la mitad de la ventana y hace un paso a la derecha
//    //Solo ahi se debe actualizar
//
//    if((BackgroundSprite::spriteImageWidthPanned + frameWidth) >= Sprite::spriteImageWidth){
//        //Recorrio toda la imagen
//        //TODO: esto es solo para el demo
//        printf("llego al limite del background");
//        Sprite::sourceRect.x = 0;
//        BackgroundSprite::spriteImageWidthPanned=0;
//    }
//    else{
//        BackgroundSprite::spriteImageWidthPanned += speedSprite;
//        Sprite::sourceRect.x += speedSprite;   //Avanzo el paneo del frame
//    }
//
//}

