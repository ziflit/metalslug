
#include "PlayerEventHandler.h"

void PlayerEventHandler::handleRealeasedKey(EventCode eventCode, Player *player) {
    Postura postura = player->getPostura();
    float direccionX = player->getDireccionX();
    switch (eventCode) {

        case EventCode::SDL_KEYLEFT_RELEASED:
            if (direccionX == -1) {
                if (postura == MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA) {
                    player->setPostura(MIRANDO_ARRIBA_IZQUIERDA_QUIETO);
                } else if (postura == CAMINANDO_IZQUIERDA) { player->setPostura(MIRANDO_IZQUIERDA_QUIETO); }
                else if (postura == AGACHADO_AVANZANDO_IZQUIERDA) {
                    player->setPostura(AGACHADO_MIRANDO_IZQUIERDA_QUIETO);
                }
                player->setDireccionX(0);
            }
                /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas */
            else if (direccionX == 0) {
                if (postura == MIRANDO_DERECHA_QUIETO) { player->setPostura(CAMINANDO_DERECHA); }
                else if (postura == AGACHADO_MIRANDO_DERECHA_QUIETO) { player->setPostura(AGACHADO_AVANZANDO_DERECHA); }
                else if (postura == MIRANDO_ARRIBA_DERECHA_QUIETO) {
                    player->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA);
                }
                player->setDireccionX(1);
            }
            break;
        case EventCode::SDL_KEYRIGHT_RELEASED:
            if (direccionX == 1) {
                if (postura == MIRANDO_ARRIBA_CAMINANDO_DERECHA) { player->setPostura(MIRANDO_ARRIBA_DERECHA_QUIETO); }
                else if (postura == CAMINANDO_DERECHA) { player->setPostura(MIRANDO_DERECHA_QUIETO); }
                else if (postura == AGACHADO_AVANZANDO_DERECHA) { player->setPostura(AGACHADO_MIRANDO_DERECHA_QUIETO); }
                player->setDireccionX(0);
            }
                /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas. */
            else if (direccionX == 0) {
                if (postura == MIRANDO_IZQUIERDA_QUIETO) { player->setPostura(CAMINANDO_IZQUIERDA); }
                else if (postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) {
                    player->setPostura(AGACHADO_AVANZANDO_IZQUIERDA);
                } else if (postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) {
                    player->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA);
                }
                player->setDireccionX(-1);
            }
            break;
        case EventCode::SDL_KEYUP_RELEASED:
            switch (postura) {
                case MIRANDO_ARRIBA_DERECHA_QUIETO:
                    player->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
                case MIRANDO_ARRIBA_IZQUIERDA_QUIETO:
                    player->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_DERECHA:
                    player->setPostura(CAMINANDO_DERECHA);
                    break;
                case MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA:
                    player->setPostura(CAMINANDO_IZQUIERDA);
                    break;
                default:
                    player->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
            }

        case EventCode::SDL_KEYDOWN_RELEASED:
            switch (postura) {
                case AGACHADO_MIRANDO_DERECHA_QUIETO:
                    player->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
                case AGACHADO_MIRANDO_IZQUIERDA_QUIETO:
                    player->setPostura(MIRANDO_IZQUIERDA_QUIETO);
                    break;
                case AGACHADO_AVANZANDO_DERECHA:
                    player->setPostura(CAMINANDO_DERECHA);
                    break;
                case AGACHADO_AVANZANDO_IZQUIERDA:
                    player->setPostura(CAMINANDO_IZQUIERDA);
                    break;
                default:
                    player->setPostura(MIRANDO_DERECHA_QUIETO);
                    break;
            }
        default:
            break;

    }
}

void PlayerEventHandler::handlePressedKey(EventCode eventCode, Player *player) {
    Postura postura = player->getPostura();
    float direccionX = player->getDireccionX();
    switch (eventCode) {
        case EventCode::SDL_KEY_A_PRESSED:
            if (!((postura == AGACHADO_MIRANDO_DERECHA_QUIETO) or (postura == AGACHADO_AVANZANDO_DERECHA) or
                  (postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == AGACHADO_AVANZANDO_IZQUIERDA))) {
                player->setDireccionY(1);
            }
            break;

        case EventCode::SDL_KEYUP_PRESSED:
            if (direccionX == 1) { player->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA); }
            else if (direccionX == -1) { player->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA); }
            else if (postura == MIRANDO_IZQUIERDA_QUIETO and
                     direccionX == 0) { player->setPostura(MIRANDO_ARRIBA_IZQUIERDA_QUIETO); }
            else { player->setPostura(MIRANDO_ARRIBA_DERECHA_QUIETO); }
            break;

        case EventCode::SDL_KEYDOWN_PRESSED:
            if (direccionX == 1) { player->setPostura(AGACHADO_AVANZANDO_DERECHA); }
            else if (direccionX == -1) { player->setPostura(AGACHADO_AVANZANDO_IZQUIERDA); }
            else if (postura == MIRANDO_IZQUIERDA_QUIETO and
                     direccionX == 0) { player->setPostura(AGACHADO_MIRANDO_IZQUIERDA_QUIETO); }
            else { player->setPostura(AGACHADO_MIRANDO_DERECHA_QUIETO); }
            break;

        case EventCode::SDL_KEYLEFT_PRESSED:
            if (direccionX == 0) {
                if ((postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or
                    (postura == MIRANDO_ARRIBA_DERECHA_QUIETO)) {
                    player->setPostura(MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA);
                } else if ((postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or
                           (postura == AGACHADO_MIRANDO_DERECHA_QUIETO)) {
                    player->setPostura(AGACHADO_AVANZANDO_IZQUIERDA);
                } else { player->setPostura(CAMINANDO_IZQUIERDA); }
                player->setDireccionX(-1);
            }
                /* Si está caminando hacia la derecha y presiona LEFT entonces queda quieto */
            else if (direccionX == 1) {
                player->setDireccionX(-1);
                player->setPostura(CAMINANDO_IZQUIERDA);
            }
            break;

        case EventCode::SDL_KEYRIGHT_PRESSED:
            if (direccionX == 0) {
                if ((postura == MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or
                    (postura == MIRANDO_ARRIBA_DERECHA_QUIETO)) {
                    player->setPostura(MIRANDO_ARRIBA_CAMINANDO_DERECHA);
                }
                else if ((postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or
                         (postura == AGACHADO_MIRANDO_DERECHA_QUIETO)) {
                    player->setPostura(AGACHADO_AVANZANDO_DERECHA);
                } else { player->setPostura(CAMINANDO_DERECHA); }
                player->setDireccionX(1);
            }
                /* Si está caminando hacia la izquierda y presiona RIGHT entonces queda quieto */
            else if (direccionX == -1) {
                player->setDireccionX(1);
                player->setPostura(CAMINANDO_DERECHA);
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

void PlayerEventHandler::handle(EventCode eventCode, GameObject *gameObject) {
    Player *player = (Player *) gameObject;
    if (eventCode == EventCode::CLIENT_DISCONNECT) {
        player->setPostura(DESCONECTADO);
    } else if (isKeyPressed(eventCode)) {
        handlePressedKey(eventCode, player);
    } else if (isKeyRealeased(eventCode)) {
        handleRealeasedKey(eventCode, player);
    }
}

PlayerEventHandler::PlayerEventHandler() {}
