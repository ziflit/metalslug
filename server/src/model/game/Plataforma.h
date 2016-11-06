#ifndef SRC_MODEL_GAME_PLATAFORMA_H_
#define SRC_MODEL_GAME_PLATAFORMA_H_

#include "GameObject.h"
#include "../../utils/Protocol.h"

class Plataforma : public GameObject {

public:
    Plataforma(int posX, int posY, int ancho, int largo);

    virtual ~Plataforma();

    struct event getState() override;

    void avanzar() override;
};


#endif /* SRC_MODEL_GAME_PLATAFORMA_H_ */
