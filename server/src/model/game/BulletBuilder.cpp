
#include "BulletBuilder.h"
#include "NormalBulletMovementStrategy.h"
#include "TeledirBulletMovementStrategy.h"
#include "NotMoveBulletStrategy.h"

Bullet *BulletBuilder::createBullet(Entity bulletType, AnimatedObject *firedBy) {
    Bullet *bullet = nullptr;
    Vector *vector = firedBy->getBulletdirection();
    if (vector->getX() == 0 && vector->getY() == 0) return nullptr;
    switch (bulletType) {
        case Entity::BT_HEAVY_BULLET:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 20, 30, 60, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
        case Entity::BT_MISSILE:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 80, 20, 30, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
        case Entity::BT_TELE_MISSILE:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new TeledirBulletMovementStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 150, 5, 10, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
        case Entity::BT_SHOT:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NotMoveBulletStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 50, 35, 20, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
        case Entity::BT_BOMB:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho() / 2,
                                firedBy->getY() + firedBy->getBoxAlto(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(),
                                firedBy->getShootsTo(), new NormalBulletMovementStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 50, 35, 20, 0, -1, firedBy->getShootsTo());
            break;
        case Entity::BT_LASER:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(), firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NotMoveBulletStrategy(), firedBy);
            setupBullet(bullet, 20, 20, 50, 35, 20, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
        default:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(),
                                firedBy->getY() + firedBy->getBoxAlto() / 2,
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy(), firedBy);

            setupBullet(bullet, 20, 20, 10, 10, 50, vector->getX(), vector->getY(), firedBy->getShootsTo());
            break;
    }
    return bullet;
}

void BulletBuilder::setupBullet(Bullet *bullet, int boxAlto, int boxAncho, int damage, int speed, int bulletScore,
                                int directionX,
                                int directionY, vector<Entity> &collisionables) {
    bullet->setBoxAlto(boxAlto);
    bullet->setBoxAncho(boxAncho);
    bullet->setDamage(damage);
    bullet->setSpeed(speed);
    bullet->setBulletScore(bulletScore);
    bullet->setDireccionX(directionX);
    bullet->setDireccionY(directionY);
    bullet->setColisionables(collisionables);
}
