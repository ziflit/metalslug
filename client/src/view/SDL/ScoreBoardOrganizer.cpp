#include "ScoreBoardOrganizer.h"

ScoreBoardOrganizer::ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer) {
    for(int i = 0 ; i<cantPlayers; i++) {
        this->scoreBoardSprites.push_back(new ScoreBoardSprite(i, mainRenderer));
    }
    this->mode = mode;
}

void ScoreBoardOrganizer::realize() {
    for (int i = 0 ; i < scoreBoardSprites.size() ; i++) {
        scoreBoardSprites[i]->actualizarDibujo();
        usernameTexts[i]->renderize();
        puntajeTexts[i]->renderize();
    }
}

void ScoreBoardOrganizer::setData(vector<PlayerSprite *> playersSprites) {
    for (int i = 0 ; i < scoreBoardSprites.size() ; i++ ) {
        PlayerSprite* player = playersSprites[i];
        this->usernameTexts.push_back(player->getUsernameTextbox());
        TextBox* puntajeTextBox = new TextBox(player->getPuntaje(),player->getRenderer(),{0,0,255,0});
        puntajeTexts.push_back(puntajeTextBox);
    }
    this->setTextPositions();
}

void ScoreBoardOrganizer::setTextPositions() {
    for(int i = 0 ; i<scoreBoardSprites.size() ; i++) {
        usernameTexts[i]->setPosition(usernameX[i], usernameY[i]);
        puntajeTexts[i]->setPosition(puntajeX[i], puntajeY[i]);
    }
}
