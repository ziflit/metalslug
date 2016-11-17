#ifndef SRC_UTILS_XMLLOADER_H_
#define SRC_UTILS_XMLLOADER_H_

#include "../Protocol.h"
#include <iostream>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string.h>
#include <map>

using namespace std;
using namespace rapidxml;

class XmlLoader {
private:
    string path;
    string pathLevelsConfig;

    map<string, Entity> entities = {
            {"MARCO",                 MARCO},
            {"TARMA",                 TARMA},
            {"FIO",                   FIO},
            {"ERI",                   ERI},
            {"BACKGROUND_LVL1_Z0",    BACKGROUND_LVL1_Z0},
            {"BACKGROUND_LVL1_Z1",    BACKGROUND_LVL1_Z1},
            {"BACKGROUND_LVL1_Z2",    BACKGROUND_LVL1_Z2},
            {"BACKGROUND_LVL2_Z0",    BACKGROUND_LVL2_Z0},
            {"BACKGROUND_LVL2_Z1",    BACKGROUND_LVL2_Z1},
            {"BACKGROUND_LVL2_Z2",    BACKGROUND_LVL2_Z2},
            {"BACKGROUND_LVL3_Z0",    BACKGROUND_LVL3_Z0},
            {"BACKGROUND_LVL3_Z1",    BACKGROUND_LVL3_Z1},
            {"BACKGROUND_LVL3_Z2",    BACKGROUND_LVL3_Z2},
            {"ENEMY_NORMAL_1",        ENEMY_NORMAL_1},
            {"ENEMY_NORMAL_2",        ENEMY_NORMAL_2},
            {"ENEMY_NORMAL_3",        ENEMY_NORMAL_3},
            {"BT_BULLET",             BT_BULLET},
            {"BT_HEAVY_BULLET",       BT_HEAVY_BULLET},
            {"BT_MISSILE",            BT_MISSILE},
            {"BT_TELE_MISSILE",       BT_TELE_MISSILE},
            {"BT_SHOT",               BT_SHOT},
            {"BT_BOMB",               BT_BOMB},
            {"MSC_WEAPON_BOX_CHASER", MSC_WEAPON_BOX_CHASER},
            {"MSC_WEAPON_BOX_HEAVY",  MSC_WEAPON_BOX_HEAVY},
            {"MSC_WEAPON_BOX_ROCKET", MSC_WEAPON_BOX_ROCKET},
            {"MSC_WEAPON_BOX_SHOT",   MSC_WEAPON_BOX_SHOT},
            {"MSC_POWER_BONUS",       MSC_POWER_BONUS},
            {"MSC_BONUS_KILLALL",     MSC_BONUS_KILLALL}
    };


public:

    XmlLoader(string path, string pathLevelsConfig);

    virtual ~XmlLoader();

    struct xmlConfig obtainGlobalConfig();

    vector<struct xmlPlayer> obtainPlayersConfig();

    vector<struct xmlEnemy> obtainEnemiesConfig();

    vector<struct xmlBackground> obtainBackgroundsConfig();

    vector<struct xmlLvl> obtainLvlsConfig();

    vector<struct xmlBullet> obtainBulletsConfig();

    vector<struct xmlMiscelanea> obtainMiscelaneasConfig();

    Entity convertToEntity(string id);
};

#endif /* SRC_UTILS_XMLLOADER_H_ */
