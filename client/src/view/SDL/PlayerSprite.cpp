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
    PlayerSprite::sourceRect.y = (frameHeight*2);
}

void PlayerSprite::rightStep() {

    PlayerSprite::sourceRect.y = (frameHeight*0);
    PlayerSprite::setNextSpriteFrame();
}

void PlayerSprite::leftStep() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = (frameHeight*3);
}

void PlayerSprite::downArrowPress() {
    PlayerSprite::setNextSpriteFrame();
    PlayerSprite::sourceRect.y = (frameHeight*1);
}

void PlayerSprite::moveRight() {
/* mueve el sprite en eje X hacia la derecha.
 * Si el sprite tiene coordenadas (mitad de pantalla, y)
 * entonces no sigue avanzando hacia la derecha
 * Solo va a poder avanzar mas de la mitad de pantalla si
 * el BackgroundSprite llego a su ultimo frame.
*/
    PlayerSprite::rightStep();
//    PlayerSprite::set_position(PlayerSprite::destRect.x + speedSprite, PlayerSprite::destRect.y);}
    int newPos = (PlayerSprite::destRect.x + speedSprite);
    if(newPos < (window_width/2)){  //TODO: ESTA LOGICA DEBE IR EN EL MODELO, NO ACA.
        PlayerSprite::set_position(newPos, PlayerSprite::destRect.y);}
}

void PlayerSprite::moveLeft() {
//    PlayerSprite::set_position(PlayerSprite::destRect.x - speedSprite, PlayerSprite::destRect.y);}

    PlayerSprite::leftStep();
    int newPos = (PlayerSprite::destRect.x - speedSprite);
    if(newPos > 0){ //TODO: ESTA LOGICA DEBE IR EN EL MODELO, NO ACA
        PlayerSprite::set_position(newPos, PlayerSprite::destRect.y);}
}

void PlayerSprite::jump() {
}

//_________________________________________________________________________________________________________


bool PlayerSprite::isInHalfWindow() {
    return (PlayerSprite::destRect.x >= ((window_width/2)-speedSprite));
}

void PlayerSprite::setNextSpriteFrame() {
    if (PlayerSprite::wActualPosFrame == (PlayerSprite::wFramesCant - 1)) {
        PlayerSprite::wActualPosFrame = 0;
    }
    PlayerSprite::sourceRect.x = (PlayerSprite::frameWidth * PlayerSprite::wActualPosFrame);
    PlayerSprite::wActualPosFrame++;
}

//_________________________________________________________________________________________________________

void PlayerSprite::handlePlayerEvents(SDL_Event event,BackgroundSprite* backgroundSprite1,BackgroundSprite* front){
        if (event.type == SDL_KEYDOWN){  //si aprieto tal tecla:
            switch (event.key.keysym.sym){

                case SDLK_LEFT:
                    PlayerSprite::moveLeft();
                    break;
                case SDLK_RIGHT:
                    PlayerSprite::moveRight();
                    
                    if(PlayerSprite::isInHalfWindow()){
                        backgroundSprite1->setNextSpriteFrame();
                        front->setNextSpriteFrame();
                    }
                    break;
                case SDLK_UP:
                    PlayerSprite::upArrowPress();
                    break;
                case SDLK_DOWN:
                    PlayerSprite::downArrowPress();
                    break;
                default:
                    break;
            }
        }

        else if(event.type == SDL_KEYUP){   //si dejo de apretar una tecla
            switch (event.key.keysym.sym){
                case SDLK_1:
                    printf("solte el 1");
            }
        }

        else if(event.type == SDL_MOUSEBUTTONDOWN){

            if (event.button.button == SDL_BUTTON_LEFT){
                printf("suelto click izq");
            }
            else if(event.button.button == SDL_BUTTON_RIGHT){
                printf("suelto click derecho");
            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP){
            if(event.button.clicks == 2){ //doble click
                printf("doble click");
            }
        }

}

