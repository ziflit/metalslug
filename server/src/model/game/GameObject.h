#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include "../../utils/Protocol.h"

class GameObject {
protected:
    Entity id;
    float x, y;
    double largeImage;
    float speed;

public:

    virtual struct event getState()= 0;

    virtual void avanzar()= 0;

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
};

#endif //SERVER_GAMEOBJECT_H
