
#include "PlayerEventHandler.h"

void PlayerEventHandler::handleRealeasedKey(EventCode eventCode, AnimatedObject *animatedObject) {
    Postura postura = animatedObject->getPostura();
    float direccionX = animatedObject->getDireccionX();
    switch (eventCode) {

        case EventCode::SDL_KEYLEFT_RELEASED:
            if (direccionX == -1) {
                if (postura == MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_IZQUIERDA_QUIETO);
                    animatedObject->updateBulletdirection(0, 1);
                } else if (postura == CAMINANDO_IZQUIERDA) {
                    animatedObject->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    animatedObject->updateBulletdirection(-1, 0);
                } else if (postura == AGACHADO_AVANZANDO_IZQUIERDA) {
                    animatedObject->setPostura(AGACHADO_MIRANDO_IZQUIERDA_QUIETO);
                    animatedObject->updateBulletdirection(0, 0);
                }
                animatedObject->setDireccionX(0);
            }
                /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas */
            else if (direccionX == 0) {
                if (postura == MIRANDO_DERECHA_QUIETO) {
                    animatedObject->setPostura(CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(1, 0);
                } else if (postura == AGACHADO_MIRANDO_DERECHA_QUIETO) {
                    animatedObject->setPostura(AGACHADO_AVANZANDO_DERECHA);
                    animatedObject->updateBulletdirection(0, 0);
                } else if (postura == MIRANDO_ARRIBA_DERECHA_QUIETO) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(0, 1);
                }
                animatedObject->setDireccionX(1);
            }
            break;
        case EventCode::SDL_KEYRIGHT_RELEASED:
            if (direccionX == 1) {
                if (postura == MIRANDO_ARRIBA_CAMINANDO_DERECHA) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(0, 1);
                } else if (postura == CAMINANDO_DERECHA) {
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(1, 0);
                } else if (postura == AGACHADO_AVANZANDO_DERECHA) {
                    animatedObject->setPostura(AGACHADO_MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(0, 0);
                }
                animatedObject->setDireccionX(0);
            }
                /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas. */
            else if (direccionX == 0) {
                if (postura == MIRANDO_IZQUIERDA_QUIETO) {
                    animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(-1, 0);
                } else if (postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) {
                    animatedObject->setPostura(AGACHADO_AVANZANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(0, 0);
                } else if (postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(0, 1);
                }
                animatedObject->setDireccionX(-1);
            }
            break;
        case EventCode::SDL_KEYUP_RELEASED:
            switch (postura) {
                case MIRANDO_ARRIBA_DERECHA_QUIETO:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
                case MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    animatedObject->updateBulletdirection(-1, 0);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_DERECHA:
                    animatedObject->setPostura(CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA:
                    animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(-1, 0);
                    break;
                default:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
            }
            break;
        case EventCode::SDL_KEYDOWN_RELEASED:
            switch (postura) {
                case AGACHADO_MIRANDO_DERECHA_QUIETO:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
                case AGACHADO_MIRANDO_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    animatedObject->updateBulletdirection(-1, 0);
                    break;
                case AGACHADO_AVANZANDO_DERECHA:
                    animatedObject->setPostura(CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
                case AGACHADO_AVANZANDO_IZQUIERDA:
                    animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(-1, 0);
                    break;
                default:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    animatedObject->updateBulletdirection(1, 0);
                    break;
            }
            break;
        case EventCode::SDL_KEY_S_RELEASED:
            switch (postura) {
                case DISPARANDO_AGACHADO_QUIETO_DERECHA:
                    animatedObject->setPostura(AGACHADO_MIRANDO_DERECHA_QUIETO);
                    break;
                case DISPARANDO_AGACHADO_QUIETO_IZQUIERDA:
                    animatedObject->setPostura(AGACHADO_MIRANDO_IZQUIERDA_QUIETO);
                    break;
                case DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_DERECHA:
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA);
                    break;
                case DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_IZQUIERDA:
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA);
                    break;
                case DISPARANDO_MIRANDO_ARRIBA_DERECHA_QUIETO:
                    animatedObject->setPostura(MIRANDO_ARRIBA_DERECHA_QUIETO);
                    break;
                case DISPARANDO_MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(MIRANDO_ARRIBA_IZQUIERDA_QUIETO);
                    break;
                case DISPARANDO_CAMINANDO_DERECHA:
                    animatedObject->setPostura(CAMINANDO_DERECHA);
                    break;
                case DISPARANDO_CAMINANDO_IZQUIERDA:
                    animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                    break;
                case DISPARANDO_DERECHA_QUIETO:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
                case DISPARANDO_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    break;
                default:
                    animatedObject->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
            }
            animatedObject->setShootingState(false);
            break;
        default:
            break;

    }
}

void PlayerEventHandler::handlePressedKey(EventCode eventCode, AnimatedObject *animatedObject) {
    Postura postura = animatedObject->getPostura();
    float direccionX = animatedObject->getDireccionX();
    switch (eventCode) {
        case EventCode::SDL_KEY_A_PRESSED:
            if (!((postura == AGACHADO_MIRANDO_DERECHA_QUIETO) or (postura == AGACHADO_AVANZANDO_DERECHA) or
                  (postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == AGACHADO_AVANZANDO_IZQUIERDA))) {
                animatedObject->setDireccionY(1);
            }
            break;

        case EventCode::SDL_KEY_S_PRESSED:
            switch (postura) {
                case AGACHADO_MIRANDO_DERECHA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_AGACHADO_QUIETO_DERECHA);
                    break;
                case AGACHADO_MIRANDO_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_AGACHADO_QUIETO_IZQUIERDA);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_DERECHA:
                    animatedObject->setPostura(DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_DERECHA);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA:
                    animatedObject->setPostura(DISPARANDO_AVANZANDO_MIRANDO_ARRIBA_IZQUIERDA);
                    break;
                case MIRANDO_ARRIBA_DERECHA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_MIRANDO_ARRIBA_DERECHA_QUIETO);
                    break;
                case MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_MIRANDO_ARRIBA_IZQUIERDA_QUIETO);
                    break;
                case CAMINANDO_DERECHA:
                    animatedObject->setPostura(DISPARANDO_CAMINANDO_DERECHA);
                    break;
                case CAMINANDO_IZQUIERDA:
                    animatedObject->setPostura(DISPARANDO_CAMINANDO_IZQUIERDA);
                    break;
                case MIRANDO_DERECHA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_DERECHA_QUIETO);
                    break;
                case MIRANDO_IZQUIERDA_QUIETO:
                    animatedObject->setPostura(DISPARANDO_IZQUIERDA_QUIETO);
                    break;
                default:
                    animatedObject->setPostura(DISPARANDO_DERECHA_QUIETO);
                    break;
            }
            animatedObject->setShootingState(true);
            break;

        case EventCode::SDL_KEYUP_PRESSED:
            if (direccionX == 1) { animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA); }
            else if (direccionX == -1) { animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA); }
            else if (postura == MIRANDO_IZQUIERDA_QUIETO and
                     direccionX == 0) { animatedObject->setPostura(MIRANDO_ARRIBA_IZQUIERDA_QUIETO); }
            else { animatedObject->setPostura(MIRANDO_ARRIBA_DERECHA_QUIETO); }
            animatedObject->updateBulletdirection(0, 1);
            break;

        case EventCode::SDL_KEYDOWN_PRESSED:
            if (direccionX == 1) {
                animatedObject->setPostura(AGACHADO_AVANZANDO_DERECHA);

            } else if (direccionX == -1) {
                animatedObject->setPostura(AGACHADO_AVANZANDO_IZQUIERDA);
            } else if (postura == MIRANDO_IZQUIERDA_QUIETO and direccionX == 0) {
                animatedObject->setPostura(AGACHADO_MIRANDO_IZQUIERDA_QUIETO);
            } else {
                animatedObject->setPostura(AGACHADO_MIRANDO_DERECHA_QUIETO);
            }
            animatedObject->updateBulletdirection(0, 0);
            break;

        case EventCode::SDL_KEYLEFT_PRESSED:
            if (direccionX == 0) {
                if ((postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or
                    (postura == MIRANDO_ARRIBA_DERECHA_QUIETO)) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(0, 1);
                } else if ((postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or
                           (postura == AGACHADO_MIRANDO_DERECHA_QUIETO)) {
                    animatedObject->setPostura(AGACHADO_AVANZANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(0, 0);
                } else {
                    animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                    animatedObject->updateBulletdirection(-1, 0);
                }
                animatedObject->setDireccionX(-1);
            }
                /* Si está caminando hacia la derecha y presiona LEFT entonces queda quieto */
            else if (direccionX == 1) {
                animatedObject->setDireccionX(-1);
                animatedObject->setPostura(CAMINANDO_IZQUIERDA);
                animatedObject->updateBulletdirection(-1, 0);
            }
            break;

        case EventCode::SDL_KEYRIGHT_PRESSED:
            if (direccionX == 0) {
                if ((postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or
                    (postura == MIRANDO_ARRIBA_DERECHA_QUIETO)) {
                    animatedObject->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(0, 1);
                } else if ((postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or
                           (postura == AGACHADO_MIRANDO_DERECHA_QUIETO)) {
                    animatedObject->setPostura(AGACHADO_AVANZANDO_DERECHA);
                    animatedObject->updateBulletdirection(0, 0);
                } else {
                    animatedObject->setPostura(CAMINANDO_DERECHA);
                    animatedObject->updateBulletdirection(1, 0);
                }
                animatedObject->setDireccionX(1);
            }
                /* Si está caminando hacia la izquierda y presiona RIGHT entonces queda quieto */
            else if (direccionX == -1) {
                animatedObject->setDireccionX(1);
                animatedObject->setPostura(CAMINANDO_DERECHA);
                animatedObject->updateBulletdirection(1, 0);
            }
            break;

        default:
            break;
    }
}

bool PlayerEventHandler::isKeyPressed(EventCode eventCode) {
    return ((eventCode == SDL_KEY_A_PRESSED) or (eventCode == SDL_KEY_S_PRESSED) or
            (eventCode == SDL_KEYUP_PRESSED) or (eventCode == SDL_KEYDOWN_PRESSED) or
            (eventCode == SDL_KEYLEFT_PRESSED) or (eventCode == SDL_KEYRIGHT_PRESSED));
}

bool PlayerEventHandler::isKeyRealeased(EventCode eventCode) {
    return ((eventCode == SDL_KEY_A_RELEASED) or (eventCode == SDL_KEY_S_RELEASED) or
            (eventCode == SDL_KEYUP_RELEASED) or (eventCode == SDL_KEYDOWN_RELEASED) or
            (eventCode == SDL_KEYLEFT_RELEASED) or (eventCode == SDL_KEYRIGHT_RELEASED));
}

void PlayerEventHandler::handle(EventCode eventCode, AnimatedObject *animatedObject) {
    if (eventCode == EventCode::CLIENT_DISCONNECT) {
        animatedObject->setPostura(DESCONECTADO);
    } else if (isKeyPressed(eventCode)) {
        handlePressedKey(eventCode, animatedObject);
    } else if (isKeyRealeased(eventCode)) {
        handleRealeasedKey(eventCode, animatedObject);
    }
}

PlayerEventHandler::PlayerEventHandler() {

}
