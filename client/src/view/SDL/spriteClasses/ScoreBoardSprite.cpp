#include "ScoreBoardSprite.h"

void ScoreBoardSprite::setPlayerBoard(int boardNumber) {
    this->setUpImage(path[boardNumber]);
    this->set_position(x[boardNumber],y[boardNumber]);
}

