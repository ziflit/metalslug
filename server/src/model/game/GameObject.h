#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include "../../utils/Protocol.h"
#include <vector>

class GameObject {
    protected:
    Entity id;
    float x, y;
    double largeImage;
    float speed;
    int box_alto;
    int box_ancho;
    vector<Entity> colisionables;

    public:

    virtual struct event getState()= 0;

    virtual void avanzar()= 0;

    int retroceder(int cantidad);

    Entity getEntity() const;

    void setEntity(Entity entity);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    double getLarge() const;

    void setLarge(double largeImage);

    float getSpeed() const;

    void setSpeed(float speed);

    int getBoxAlto() const;

    void setBoxAlto(int boxAlto);

    int getBoxAncho() const;

    void setBoxAncho(int boxAncho);

    bool checkCollition(int newX, int newY ,GameObject* other_object);

    bool puedenColisionar(GameObject *otherObj);
};

#endif //SERVER_GAMEOBJECT_H
