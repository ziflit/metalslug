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
    vector<TextBox*> extraTexts;
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
            {1, 550},
            {2, 220},
            {3, 550}
    };
    map<int, int> puntajeY = {
            {0, 220},
            {1, 220},
            {2, 380},
            {3, 380}
    };
public:

    ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer);

    void realize();

    void setData(vector<PlayerSprite *> playersSprites);

    void setTextPositions();

    int sumColavorative(std::vector<PlayerSprite *> vector);

    int sumGrupal0(std::vector<PlayerSprite *> vector);

    int sumGrupal1(std::vector<PlayerSprite *> vector);

    void updateTotals(std::vector<PlayerSprite *> vector);
};


#endif //METALSLUG_SCOREBOARD_H
