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
        for (int i = 0 ; extraTexts.size(); i++) {
            extraTexts[i]->renderize();
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
            updateTotals(playersSprites);
        }
        return;
    }

    for (int i = 0 ; i < scoreBoardSprites.size() ; i++ ) {
        PlayerSprite* player = playersSprites[i];
        usernameTexts.push_back(new TextBox(player->getUsername(), player->getRenderer(), {0,0,255,0},28));
        puntajeTexts.push_back(new TextBox(player->getPuntaje(),player->getRenderer(),{0,0,255,0},28));
    }
    this->setTextPositions();

    if((mode == COLABORATIVO) and (playersSprites.size()>1)) {
        TextBox* text1 = new TextBox(this->sumColavorative(playersSprites), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text1->setPosition(300, 500);
        extraTexts.push_back(text1);
        TextBox* text = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text->setPosition(150, 500);
        extraTexts.push_back(text);
    } else if ((mode == GRUPAL) and (playersSprites.size() > 2) ){
        TextBox* text0 = new TextBox(this->sumGrupal(playersSprites,0), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text0->setPosition(220, 500);
        extraTexts.push_back(text0);
        TextBox* text1 = new TextBox(this->sumGrupal(playersSprites,1), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text1->setPosition(400, 500);
        extraTexts.push_back(text1);
        TextBox* text2 = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text2->setPosition(25, 500);
        extraTexts.push_back(text2);
        TextBox* text3 = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text3->setPosition(300, 500);
        extraTexts.push_back(text3);

    }
}

void ScoreBoardOrganizer::setTextPositions() {
    for(int i = 0 ; i<scoreBoardSprites.size() ; i++) {
        usernameTexts[i]->setPosition(usernameX[i], usernameY[i]);
        puntajeTexts[i]->setPosition(puntajeX[i], puntajeY[i]);
    }
}

int ScoreBoardOrganizer::sumColavorative(vector<PlayerSprite *> vector) {
    return sumGrupal(vector,0) + sumGrupal(vector,1);
}

int ScoreBoardOrganizer::sumGrupal(std::vector<PlayerSprite *> vector,int grupo) {
    int sum = 0;
    for (int i ; i < vector.size() ; i++){
        if ((i % 2) == grupo){
            sum += vector[i]->getPuntaje();
        }
    }
    return sum;
}

void ScoreBoardOrganizer::updateTotals(std::vector<PlayerSprite *> vector) {
    if (mode == COLABORATIVO) {
        extraTexts[0]->changeText(sumColavorative(vector));
    } else if (mode == GRUPAL) {
        extraTexts[0]->changeText(sumGrupal(vector,0));
        extraTexts[1]->changeText(sumGrupal(vector,1));
    }
}