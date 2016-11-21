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

    if(mode == COLABORATIVO) {
        TextBox* text1 = new TextBox(this->sumColavorative(playersSprites), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text1->setPosition(200, 500);
        extraTexts.push_back(text1);
        TextBox* text = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text->setPosition(100, 500);
        extraTexts.push_back(text);
    } else if (mode == GRUPAL) {
        TextBox* text0 = new TextBox(this->sumGrupal0(playersSprites), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text0->setPosition(200, 500);
        extraTexts.push_back(text0);
        TextBox* text1 = new TextBox(this->sumGrupal1(playersSprites), playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text1->setPosition(500, 500);
        extraTexts.push_back(text1);
        TextBox* text2 = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text2->setPosition(10, 500);
        extraTexts.push_back(text2);
        TextBox* text3 = new TextBox("TOTAL:", playersSprites[0]->getRenderer(),{0,0,255,0},50);
        text3->setPosition(410, 500);
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
    int sum = 0;
    for (int i ; i < vector.size() ; i++){
        sum += vector[i]->getPuntaje();
    }
    return sum;
}

int ScoreBoardOrganizer::sumGrupal0(std::vector<PlayerSprite *> vector) {
    int sum = 0;
    for (int i ; i < vector.size() ; i++){
        if (i%2 == 0){
            sum += vector[i]->getPuntaje();
        }
    }
    return sum;
}

int ScoreBoardOrganizer::sumGrupal1(std::vector<PlayerSprite *> vector) {
    int sum = 0;
    for (int i ; i < vector.size() ; i++){
        if (i%2 == 1){
            sum += vector[i]->getPuntaje();
        }
    }
    return sum;
}

void ScoreBoardOrganizer::updateTotals(std::vector<PlayerSprite *> vector) {
    if (mode == COLABORATIVO) {
        extraTexts[0]->changeText(sumColavorative(vector));
    } else if (mode == GRUPAL) {
        extraTexts[0]->changeText(sumGrupal0(vector));
        extraTexts[1]->changeText(sumGrupal1(vector));
    }
}

