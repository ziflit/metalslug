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
    xmlGameMode mode;
    map<int, function<Player *(std::string, int, int)>> playerCreator = {
            {0, [](string user, int windowWidth, int groupId) -> Player * {
                return new Player(user, MARCO, windowWidth, groupId);
            }},
            {1, [](string user, int windowWidth, int groupId) -> Player * {
                return new Player(user, FIO, windowWidth, groupId);
            }},
            {2, [](string user, int windowWidth, int groupId) -> Player * {
                return new Player(user, TARMA, windowWidth, groupId);
            }},
            {3, [](string user, int windowWidth, int groupId) -> Player * {
                return new Player(user, ERI, windowWidth, groupId);
            }}};
public:

    Player *createPlayer(int playerNumber, string user, int windowWidth);

    void setGameMode(xmlGameMode mode);

    int getGroupId(int playerNumber);

    int getHealth();
};

#endif //SERVER_PLAYERBUILDER_H
