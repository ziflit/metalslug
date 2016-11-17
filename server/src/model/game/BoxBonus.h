#ifndef SRC_MODEL_GAME_BOXBONUS_H_
#define SRC_MODEL_GAME_BOXBONUS_H_

#include "GameObject.h"
#include "../../utils/Protocol.h"

class BoxBonus : public GameObject {

public:
    BoxBonus(int posX, int posY);

    virtual ~BoxBonus();

    struct event getState() override;

    void avanzar(vector<GameObject *> gameObjects) override;
};


#endif /* SRC_MODEL_GAME_BOXBONUS_H_ */
