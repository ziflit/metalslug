#ifndef METALSLUG_SCORETABLE_H
#define METALSLUG_SCORETABLE_H


#include <SDL2/SDL_system.h>
#include <map>
#include "Sprite.h"

class ScoreBoardSprite : public Sprite{
private:
    map<int, string> path = {
            {0, "sprites/scoreBoards/marcoScoreBoard.png"},
            {1, "sprites/scoreBoards/marcoScoreBoard.png"},
            {2, "sprites/scoreBoards/marcoScoreBoard.png"},
            {3, "sprites/scoreBoards/marcoScoreBoard.png"}
    };

    map<int, int> x = {
            {0, 50},
            {1, 450},
            {2, 50},
            {3, 450}
    };

    map<int, int> y = {
            {0, 275},
            {1, 275},
            {2, 475},
            {3, 475}
    };

    void setPlayerBoard(int boardNumber);
public:

    ScoreBoardSprite(int boardNumber, SDL_Renderer *mainRenderer) : Sprite(mainRenderer) {
        this->setPlayerBoard(boardNumber);
        this->sourceRect.w = 300;
        this->sourceRect.h = 150;
        this->setWidth(300);
        this->setHeight(150);
    }

    virtual void setUpImage(string imageSpritePath) override;

    virtual void handle(struct event nuevoEvento) override;
};
#endif //METALSLUG_SCORETABLE_H