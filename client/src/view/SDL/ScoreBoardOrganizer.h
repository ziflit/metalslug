#ifndef METALSLUG_SCOREBOARD_H
#define METALSLUG_SCOREBOARD_H


#include <SDL2/SDL_system.h>
#include "../../utils/Protocol.h"
#include "spriteClasses/ScoreBoardSprite.h"
#include "spriteClasses/PlayerSprite.h"

class ScoreBoardOrganizer {
private:
    GameMode mode;
    bool renderize;
    vector<ScoreBoardSprite*> scoreBoardSprites;
    vector<TextBox*> usernameTexts;
    vector<TextBox*> puntajeTexts;
    map<int, int> usernameX = {
            {0, 170},
            {1, 600},
            {2, 170},
            {3, 600}
    };
    map<int, int> usernameY = {
            {0, 140},
            {1, 140},
            {2, 363},
            {3, 363}
    };
    map<int, int> puntajeX = {
            {0, 220},
            {1, 600},
            {2, 220},
            {3, 600}
    };
    map<int, int> puntajeY = {
            {0, 220},
            {1, 220},
            {2, 435},
            {3, 435}
    };
public:
    ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer);

    void realize();

    void setData(vector<PlayerSprite *> playersSprites);

    void setTextPositions();
};


#endif //METALSLUG_SCOREBOARD_H
