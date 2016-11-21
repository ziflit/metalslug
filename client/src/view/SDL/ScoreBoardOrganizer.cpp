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
        this->renderize = false;
    }
}

void ScoreBoardOrganizer::setData(vector<PlayerSprite *> playersSprites) {
    this->renderize = true;
    if(usernameTexts.size() > 0){
        for (int i = 0 ; i < usernameTexts.size() ; i++) {
            usernameTexts[i]->changeText(playersSprites[i]->getUsername());
            puntajeTexts[i]->changeText(playersSprites[i]->getPuntaje());
        }
        return;
    }
    for (int i = 0 ; i < scoreBoardSprites.size() ; i++ ) {
        PlayerSprite* player = playersSprites[i];

        usernameTexts.push_back(new TextBox(player->getUsername(), player->getRenderer(), {0,0,255,0},28));
        puntajeTexts.push_back(new TextBox(player->getPuntaje(),player->getRenderer(),{0,0,255,0},28));
    }
    this->setTextPositions();
}

void ScoreBoardOrganizer::setTextPositions() {
    for(int i = 0 ; i<scoreBoardSprites.size() ; i++) {
        usernameTexts[i]->setPosition(usernameX[i], usernameY[i]);
        puntajeTexts[i]->setPosition(puntajeX[i], puntajeY[i]);
    }
}