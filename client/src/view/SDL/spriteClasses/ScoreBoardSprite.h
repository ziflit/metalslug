#ifndef METALSLUG_SCORETABLE_H
#define METALSLUG_SCORETABLE_H


#include <SDL2/SDL_system.h>
#include <map>
#include "Sprite.h"

class ScoreBoardSprite : Sprite{
private:
    map<int, string> path = {
            {0, "sprites/scoreBoards/marcoScoreBoard.png"},
            {1, "sprites/scoreBoards/marcoScoreBoard.png"},
            {2, "sprites/scoreBoards/marcoScoreBoard.png"},
            {3, "sprites/scoreBoards/marcoScoreBoard.png"}
    };

    map<int, int> x = {
            {0, 10},
            {1, 350},
            {2, 10},
            {3, 350}
    };

    map<int, int> y = {
            {0, 40},
            {1, 300},
            {2, 40},
            {3, 300}
    };

public:

    void setPlayerBoard(int boardNumber);

    ScoreBoardSprite(int boardNumber, SDL_Renderer *mainRenderer) : Sprite(mainRenderer) {
        this->setPlayerBoard(boardNumber);
        this->setWidth(250);
        this->setHeight(200);
    }
};


#endif //METALSLUG_SCORETABLE_H
