/*
 * Player.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_PLAYER_H_
#define SRC_MODEL_GAME_PLAYER_H_

#include <string>
#include <vector>
#include "../../utils/Protocol.h"
#include "AnimatedObject.h"
#include "Bullet.h"

class Player : public AnimatedObject {
private:
    string username;
    int posAtJump;
    int gravity;
    int jumpPos[25] = {0, 23, 44, 63, 80, 95, 108, 119, 128, 135, 140, 143, 144,
                       143, 140, 135, 128, 119, 108, 95, 80, 63, 44, 23, 0};
    int windowWidth;
    vector<Entity> shootsTo = {ENEMY_NORMAL_1, ENEMY_NORMAL_2, ENEMY_NORMAL_3, ENEMY_FINAL_1,
                               ENEMY_FINAL_2, ENEMY_FINAL_3, MSC_PLATFORM};

public:
    Player(string user, Entity entitySelected, int windowWidth);

    virtual ~Player();

    struct event getState() override;

    bool isMoving();

    bool haveBullets();

    GameObject *shoot() override ;

    void avanzar(vector<GameObject *> game_objects) override { x += speed; };

    void retroceder();

    void updatePosition(vector<GameObject *> game_objects);

    void set_position(int posx, int posy);

    bool canIMove(vector<GameObject *> game_objects, int newX, int newY);

    //getters y setters -----------------------------------------------------------------------------------------

    string getUsername() const {
        return username;
    }

};


#endif /* SRC_MODEL_GAME_PLAYER_H_ */
