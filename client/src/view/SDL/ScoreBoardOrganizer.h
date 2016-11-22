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
            {0, 180},
            {1, 590},
            {2, 180},
            {3, 590}
    };
    map<int, int> usernameY = {
            {0, 140},
            {1, 140},
            {2, 340},
            {3, 340}
    };
    map<int, int> puntajeX = {
            {0, 200},
            {1, 610},
            {2, 200},
            {3, 610}
    };
    map<int, int> puntajeY = {
            {0, 210},
            {1, 210},
            {2, 410},
            {3, 410}
    };
public:

    ScoreBoardOrganizer(GameMode mode, int cantPlayers, SDL_Renderer *mainRenderer);

    void realize();

    void setData(vector<PlayerSprite *> playersSprites);

    void setTextPositions();

    int sumColavorative(std::vector<PlayerSprite *> vector);

    int sumGrupal(std::vector<PlayerSprite *> vector,int grupo);

    void updateTotals(std::vector<PlayerSprite *> vector);
};


#endif //METALSLUG_SCOREBOARD_H
