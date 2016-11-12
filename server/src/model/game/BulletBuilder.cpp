
#include "BulletBuilder.h"
#include "NormalBulletMovementStrategy.h"
#include "TeledirBulletMovementStrategy.h"
#include "NotMoveBulletStrategy.h"

Bullet *BulletBuilder::createBullet(Entity bulletType, AnimatedObject *firedBy) {
    Bullet *bullet = nullptr;
    switch (bulletType) {
        case Entity::BT_HEAVY_BULLET:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(), firedBy->getY(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy());
            setupBullet(bullet, 50, 50, 100, 60, 0, 0);
            break;
        case Entity::BT_MISSILE:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(), firedBy->getY(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy());
            setupBullet(bullet, 50, 50, 100, 30, 0, 0);
            break;
        case Entity::BT_TELE_MISSILE:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(), firedBy->getY(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new TeledirBulletMovementStrategy());
            setupBullet(bullet, 50, 50, 100, 10, 0, 0);
            break;
        case Entity::BT_SHOT:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(), firedBy->getY(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NotMoveBulletStrategy());
            setupBullet(bullet, 50, 50, 200, 20, 0, 0);
            break;
        default:
            bullet = new Bullet(bulletType, firedBy->getX() + firedBy->getBoxAncho(), firedBy->getY(),
                                firedBy->getDireccionX(),
                                firedBy->getDireccionY(), firedBy->getShootsTo(),
                                new NormalBulletMovementStrategy());
            setupBullet(bullet, 50, 50, 100, 50, 0, 0);
            break;
    }
    return bullet;
}

void BulletBuilder::setupBullet(Bullet *bullet, int boxAlto, int boxAncho, int damage, int speed, int directionX,
                                int directionY) {
    bullet->setBoxAlto(boxAlto);
    bullet->setBoxAncho(boxAncho);
    bullet->setDamage(damage);
    bullet->setSpeed(speed);
    bullet->setDireccionX(directionX);
    bullet->setDireccionY(directionY);
}
