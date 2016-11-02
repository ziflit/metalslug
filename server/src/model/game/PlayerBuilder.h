//
// Created by leandro on 30/10/16.
//

#ifndef SERVER_PLAYERBUILDER_H
#define SERVER_PLAYERBUILDER_H

#include <functional>
#include <map>
#include "Player.h"

using namespace std;

class PlayerBuilder {
private:
    map<int, function<Player *(std::string, int)>> playerCreator = {
            {0, [](string user, int windowWidth) -> Player * {
                return new Player(user, MARCO, windowWidth);
            }},
            {1, [](string user, int windowWidth) -> Player * {
                return new Player(user, FIO, windowWidth);
            }},
            {2, [](string user, int windowWidth) -> Player * {
                return new Player(user, TARMA, windowWidth);
            }},
            {3, [](string user, int windowWidth) -> Player * {
                return new Player(user, ERI, windowWidth);
            }}};
public:
    Player *createPlayer(int playerNumber, string user, int windowWidth);

};

#endif //SERVER_PLAYERBUILDER_H
