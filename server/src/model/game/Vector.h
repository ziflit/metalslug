
#ifndef SERVER_VECTOR_H
#define SERVER_VECTOR_H


class Vector {
private:
    float x;
    float y;
public:
    virtual ~Vector() {

    }

    Vector(float x, float y) : x(x), y(y) {}

    float getX() const {
        return x;
    }

    void setX(float x) {
        Vector::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        Vector::y = y;
    }
};


#endif //SERVER_VECTOR_H
