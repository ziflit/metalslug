#include "BackgroundSprite.h"

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


