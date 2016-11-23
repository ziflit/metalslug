//
// Created by mfp on 21/11/16.
//

#ifndef METALSLUG_DATABAR_H
#define METALSLUG_DATABAR_H


#include <map>
#include "Sprite.h"
#include "../sound-ttf/TextBox.h"

class DataBarSprite : public Sprite {
private:
    bool testMode;
    map<Entity , string> path = {
            {MARCO, "sprites/scoreBoards/marcoBar.png"},
            {FIO, "sprites/scoreBoards/fioBar.png"},
            {TARMA, "sprites/scoreBoards/tarmaBar.png"},
            {ERI, "sprites/scoreBoards/eriBar.png"}
    };
    map<Entity, int> healthX = {
            {MARCO, 120},
            {FIO, 520},
            {TARMA, 120},
            {ERI, 520}
    };
    map<Entity, int> healthY = {
            {MARCO, 20},
            {FIO, 20},
            {TARMA, 70},
            {ERI, 70}
    };
    map<Entity , int> scoreX = {
            {MARCO, 300},
            {FIO, 690},
            {TARMA, 300},
            {ERI, 690}
    };
    map<Entity , int> scoreY = {
            {MARCO, 18},
            {FIO, 18},
            {TARMA, 67},
            {ERI, 67}
    };
    TextBox *healthText, *scoreText;
public:
    DataBarSprite(SDL_Renderer *renderer, Entity id);

    virtual void handle(struct event nuevoEvento) override;

    void updateScore(int score);

    void updateHealth(int health);

    void updateHealth(string health);

    void actualizarDibujo();

    void setTestMode();
};


#endif //METALSLUG_DATABAR_H
