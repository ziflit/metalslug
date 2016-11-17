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
    int gravity;
    int windowWidth;
    int groupId;
public:
    int getGroupId() const;

    void setGroupId(int groupId);

public:
    Player(string user, Entity entitySelected, int windowWidth, int groupId);

    virtual ~Player();

    struct event getState() override;

    bool isMoving();

    bool haveBullets();

    GameObject *shoot() override;

    void avanzar(vector<GameObject *> game_objects) override { x += speed; };

    void retroceder();

    void updatePosition(vector<GameObject *> game_objects);

    void set_position(int posx, int posy);

    bool canIMove(vector<GameObject *> game_objects, int newX, int newY);

    string getUsername() const {
        return username;
    }
};


#endif /* SRC_MODEL_GAME_PLAYER_H_ */
