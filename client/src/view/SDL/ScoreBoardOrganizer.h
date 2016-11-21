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
            {0, 200},
            {1, 600},
            {2, 200},
            {3, 600}
    };
    map<int, int> usernameY = {
            {0, 225},
            {1, 225},
            {2, 350},
            {3, 350}
    };
    map<int, int> puntajeX = {
            {0, 200},
            {1, 600},
            {2, 200},
            {3, 600}
    };
    map<int, int> puntajeY = {
            {0, 280},
            {1, 280},
            {2, 500},
            {3, 500}
    };
public:
    ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer);

    void realize();

    void setData(vector<PlayerSprite *> playersSprites);

    void setTextPositions();
};


#endif //METALSLUG_SCOREBOARD_H
