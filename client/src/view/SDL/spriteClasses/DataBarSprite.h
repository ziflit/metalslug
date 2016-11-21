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
    map<Entity , string> path = {
            {MARCO, "sprites/scoreBoards/marcoBar.png"},
            {FIO, "sprites/scoreBoards/fioBar.png"},
            {TARMA, "sprites/scoreBoards/tarmaBar.png"},
            {ERI, "sprites/scoreBoards/eriBar.png"}
    };
    TextBox *healthText, *scoreText;
public:
    DataBarSprite(SDL_Renderer *renderer, Entity id);

    virtual void handle(struct event nuevoEvento) override;


    void handle(int health, int score);
};


#endif //METALSLUG_DATABAR_H
