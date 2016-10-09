//
// Created by mfprado on 27/09/16.
//

#include "PlayerSprite.h"


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


void PlayerSprite::upArrowPress() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = 0;
}

void PlayerSprite::rightStep() {

    PlayerSprite::sourceRect.y = (frameHeight*1);
    PlayerSprite::setNextSpriteFrame();
}

void PlayerSprite::leftStep() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = (frameHeight*2);
}

void PlayerSprite::downArrowPress() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = (frameHeight*4);
}
//_________________________________________________________________________________________________________



void PlayerSprite::setNextSpriteFrame() {
    if (PlayerSprite::wActualPosFrame == (PlayerSprite::wFramesCant - 1)) {
        PlayerSprite::wActualPosFrame = 0;
    }
    PlayerSprite::sourceRect.x = (PlayerSprite::frameWidth * PlayerSprite::wActualPosFrame);
    PlayerSprite::wActualPosFrame++;
}

//_________________________________________________________________________________________________________

