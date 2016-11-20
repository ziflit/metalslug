#ifndef SERVER_WEAPONBONUSSTRATEGY_H
#define SERVER_WEAPONBONUSSTRATEGY_H


#include <map>
#include "BonusStrategy.h"

class WeaponBonusStrategy : public BonusStrategy {
private:
    map<Entity, Entity> bulletTypes = {{MSC_WEAPON_BOX_HEAVY,  BT_HEAVY_BULLET},
                                       {MSC_WEAPON_BOX_ROCKET, BT_MISSILE},
                                       {MSC_WEAPON_BOX_CHASER, BT_TELE_MISSILE},
                                       {MSC_WEAPON_BOX_SHOT,   BT_SHOT}};
    map<Entity, int> ammoReload = {{BT_HEAVY_BULLET, 150},
                                   {BT_MISSILE,      15},
                                   {BT_TELE_MISSILE, 10},
                                   {BT_SHOT,         15}};
    map<Entity, int> ammo = {{BT_HEAVY_BULLET, 200},
                             {BT_MISSILE,      30},
                             {BT_TELE_MISSILE, 30},
                             {BT_SHOT,         40}};

    void applyBonus(Player *player, Entity entity);

    void addAmmo(Player *player, Entity &bulletType, map<Entity, int> &dictionary);

public:
    virtual void execute(GameObject *bonus, vector<GameObject *> &gameObjects, Player *player) override;


};


#endif //SERVER_WEAPONBONUSSTRATEGY_H
