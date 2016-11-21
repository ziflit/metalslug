#include "ScoreBoardOrganizer.h"

ScoreBoardOrganizer::ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer) {
    for(int i = 0 ; i<cantPlayers; i++) {
        this->scoreBoardSprites.push_back(new ScoreBoardSprite(i, mainRenderer));
    }
    this->renderize = false;
    this->mode = mode;
}

void ScoreBoardOrganizer::realize() {
    if (renderize) {
        for (int i = 0; i < scoreBoardSprites.size(); i++) {
            scoreBoardSprites[i]->actualizarDibujo();
            usernameTexts[i]->renderize();
            puntajeTexts[i]->renderize();
        }
        usernameTexts[scoreBoardSprites.size()]->renderize();
        this->renderize = false;
    }
}

void ScoreBoardOrganizer::setData(vector<PlayerSprite *> playersSprites) {
    this->renderize = true;
    for (int i = 0 ; i < scoreBoardSprites.size() ; i++ ) {
        PlayerSprite* player = playersSprites[i];

        usernameTexts.push_back(new TextBox(player->getUsername(), player->getRenderer(), {0,0,255,0},40));
        puntajeTexts.push_back(new TextBox(player->getPuntaje(),player->getRenderer(),{0,0,255,0},40));
    }
    TextBox* scores = new TextBox(21, playersSprites[0]->getRenderer(), {40,0,240,0},80);
    scores->changeText("SCORES:");
    scores->setPosition(150,10);
    usernameTexts.push_back((scores));
    this->setTextPositions();
}

void ScoreBoardOrganizer::setTextPositions() {
    for(int i = 0 ; i<scoreBoardSprites.size() ; i++) {
        usernameTexts[i]->setPosition(usernameX[i], usernameY[i]);
        puntajeTexts[i]->setPosition(puntajeX[i], puntajeY[i]);
    }
}
