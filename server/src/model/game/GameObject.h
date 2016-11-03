#ifndef SERVER_GAMEOBJECT_H
#define SERVER_GAMEOBJECT_H

#include "../../utils/Protocol.h"

class GameObject {
protected:
    Entity entity;
    float x, y;
    double large;
    float speed;
    int box_alto;
    int box_ancho;

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

    void setLarge(double large);

    float getSpeed() const;

    void setSpeed(float speed);

	int getBoxAlto() const;

	void setBoxAlto(int boxAlto);

	int getBoxAncho() const;

	void setBoxAncho(int boxAncho);
};

#endif //SERVER_GAMEOBJECT_H
