#include "XmlLoader.h"

XmlLoader::XmlLoader(string path, string pathLevelsConfig) {
    this->path = path;
    this->pathLevelsConfig = pathLevelsConfig;
}

XmlLoader::~XmlLoader() {
}

Entity XmlLoader::convertToEntity(string id) {

        if ("MARCO" == id) {
            return MARCO;
        }
        else if ("TARMA" == id) {
            return TARMA;
        }
        else if ("FIO" == id) {
            return FIO;
        }
        else if ("ERI" == id) {
            return ERI;
        }
        else if ("BACKGROUND_LVL1_Z0" == id) {
            return BACKGROUND_LVL1_Z0;
        }
        else if ("BACKGROUND_LVL1_Z1" == id) {
            return BACKGROUND_LVL1_Z1;
        }
        else if ("BACKGROUND_LVL1_Z2" == id) {
            return BACKGROUND_LVL1_Z2;
        }
        else if ("BACKGROUND_LVL2_Z0" == id) {
            return BACKGROUND_LVL2_Z0;
        }
        else if ("BACKGROUND_LVL2_Z1" == id) {
            return BACKGROUND_LVL2_Z1;
        }
        else if ("BACKGROUND_LVL2_Z2" == id) {
            return BACKGROUND_LVL2_Z2;
        }
        else if ("BACKGROUND_LVL3_Z0" == id) {
            return BACKGROUND_LVL3_Z0;
        }
        else if ("BACKGROUND_LVL3_Z1" == id) {
            return BACKGROUND_LVL3_Z1;
        }
        else if ("BACKGROUND_LVL3_Z2" == id) {
            return BACKGROUND_LVL3_Z2;
        }
        else if ("ENEMY_NORMAL_1" == id) {
            return ENEMY_NORMAL_1;
        }
        else if ("ENEMY_NORMAL_2" == id) {
            return ENEMY_NORMAL_2;
        }
        else if ("ENEMY_NORMAL_3" == id) {
            return ENEMY_NORMAL_3;
        }
        else if ("BT_BULLET" == id) {
            return BT_BULLET;
        }
        else if ("BT_HEAVY_BULLET" == id) {
            return BT_HEAVY_BULLET;
        }
        else if ("BT_MISSILE" == id) {
            return BT_MISSILE;
        }
        else if ("BT_TELE_MISSILE" == id) {
            return BT_TELE_MISSILE;
        }
        else if ("BT_SHOT" == id) {
            return BT_SHOT;
        }
        else if ("BT_BOMB" == id) {
            return BT_BOMB;
        }
        else if ("MSC_WEAPON_BOX" == id) {
            return MSC_WEAPON_BOX;
        }
        else if ("MSC_POWER_BONUS" == id) {
            return MSC_POWER_BONUS;
        }

        else if ("MSC_BONUS_KILLALL" == id) {
            return MSC_BONUS_KILLALL;
        }
        else {
            return NOPLAYER;
        }
}

vector<struct xmlBackground> XmlLoader::obtainBackgroundsConfig() {
    xml_document<> doc;
    file<> xmlFile(path.c_str());
    doc.parse<0>(xmlFile.data());
    vector<struct xmlBackground> configs;
    xml_node<> *backgrounds = doc.first_node("backgrounds");

    for (xml_node<> *background = backgrounds->first_node("background");
            background; background = background->next_sibling()) {
        xml_node<> *id = background->first_node("id");
        xml_node<> *imagen_fondo = background->first_node("imagen_fondo");
        xml_node<> *ancho = background->first_node("ancho");
        xml_node<> *alto = background->first_node("alto");

        struct xmlBackground backgroundConfig;
        backgroundConfig.completion = EventCompletion::PARTIAL_MSG;
        backgroundConfig.id = this->convertToEntity(id->value());
        backgroundConfig.ancho = atoi(ancho->value());
        backgroundConfig.alto = atoi(alto->value());
        strcpy(backgroundConfig.path, imagen_fondo->value());

        configs.push_back(backgroundConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}

vector<struct xmlPlayer> XmlLoader::obtainPlayersConfig() {
//Cargo los players
    xml_document<> doc;
    file<> xmlFile(path.c_str()); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlPlayer> configs;

    xml_node<> *players = doc.first_node("players");
    for (xml_node<> *player = players->first_node("player"); player; player = player->next_sibling()) {
        xml_node<> *id = player->first_node("id");
        xml_node<> *pathColor = player->first_node("pathColor");
        xml_node<> *pathGrey = player->first_node("pathGrey");
        xml_node<> *pathWeapons = player->first_node("pathWeapons");
        xml_node<> *ancho = player->first_node("ancho");
        xml_node<> *alto = player->first_node("alto");
        xml_node<> *cantWidthFrames = player->first_node("cantWidthFrames");
        xml_node<> *cantHeightFrames = player->first_node("cantHeightFrames");
        xml_node<> *speed = player->first_node("speed");

        struct xmlPlayer playerConfig;
        playerConfig.completion = EventCompletion::PARTIAL_MSG;
        playerConfig.id = this->convertToEntity(id->value());
        strcpy(playerConfig.pathColor, pathColor->value());
        strcpy(playerConfig.pathGrey, pathGrey->value());
        strcpy(playerConfig.pathWeapons,pathWeapons->value());
        playerConfig.ancho = atoi(ancho->value());
        playerConfig.alto = atoi(alto->value());
        playerConfig.cantWidthFrames = atoi(cantWidthFrames->value());
        playerConfig.cantHeightFrames = atoi(cantHeightFrames->value());
        playerConfig.speed = atoi(speed->value());

        configs.push_back(playerConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}

vector<struct xmlEnemy> XmlLoader::obtainEnemiesConfig() {
//Cargo los enemies
    xml_document<> doc;
    file<> xmlFile(path.c_str()); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlEnemy> configs;
    xml_node<> *enemies = doc.first_node("enemies");
    for (xml_node<> *enemy = enemies->first_node("enemy"); enemy; enemy = enemy->next_sibling()) {
        xml_node<> *id = enemy->first_node("id");
        xml_node<> *path = enemy->first_node("path");
        xml_node<> *ancho = enemy->first_node("ancho");
        xml_node<> *alto = enemy->first_node("alto");
        xml_node<> *cantWidthFrames = enemy->first_node("cantWidthFrames");
        xml_node<> *cantHeightFrames = enemy->first_node("cantHeightFrames");
        xml_node<> *speed = enemy->first_node("speed");

        struct xmlEnemy enemyConfig;
        enemyConfig.completion = EventCompletion::PARTIAL_MSG;
        enemyConfig.id = this->convertToEntity(id->value());
        strcpy(enemyConfig.path, path->value());
        enemyConfig.ancho = atoi(ancho->value());
        enemyConfig.alto = atoi(alto->value());
        enemyConfig.cantWidthFrames = atoi(cantWidthFrames->value());
        enemyConfig.cantHeightFrames = atoi(cantHeightFrames->value());
        enemyConfig.speed = atoi(speed->value());

        configs.push_back(enemyConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}


vector<struct xmlBullet> XmlLoader::obtainBulletsConfig() {
    xml_document<> doc;
    file<> xmlFile(path.c_str());
    doc.parse<0>(xmlFile.data());
    vector<struct xmlBullet> configs;
    xml_node<> *bullets = doc.first_node("bullets");

    for (xml_node<> *bullet = bullets->first_node("bullet");
         bullet; bullet = bullet->next_sibling()) {
        xml_node<> *id = bullet->first_node("id");
        xml_node<> *path = bullet->first_node("path");
        xml_node<> *ancho = bullet->first_node("ancho");
        xml_node<> *alto = bullet->first_node("alto");

        struct xmlBullet bulletConfig;
        bulletConfig.completion = EventCompletion::PARTIAL_MSG;
        bulletConfig.id = this->convertToEntity(id->value());
        bulletConfig.ancho = atoi(ancho->value());
        bulletConfig.alto = atoi(alto->value());
        strcpy(bulletConfig.path, path->value());

        configs.push_back(bulletConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}

vector<struct xmlMiscelanea> XmlLoader::obtainMiscelaneasConfig() {
    xml_document<> doc;
    file<> xmlFile(path.c_str());
    doc.parse<0>(xmlFile.data());
    vector<struct xmlMiscelanea> configs;
    xml_node<> *miscelaneas = doc.first_node("miscelaneas");

    for (xml_node<> *miscelanea = miscelaneas->first_node("miscelanea");
         miscelanea; miscelanea = miscelanea->next_sibling()) {
        xml_node<> *id = miscelanea->first_node("id");
        xml_node<> *path = miscelanea->first_node("path");
        xml_node<> *ancho = miscelanea->first_node("ancho");
        xml_node<> *alto = miscelanea->first_node("alto");

        struct xmlMiscelanea miscelaneaConfig;
        miscelaneaConfig.completion = EventCompletion::PARTIAL_MSG;
        miscelaneaConfig.id = this->convertToEntity(id->value());
        miscelaneaConfig.ancho = atoi(ancho->value());
        miscelaneaConfig.alto = atoi(alto->value());
        strcpy(miscelaneaConfig.path, path->value());

        configs.push_back(miscelaneaConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}

struct xmlConfig XmlLoader::obtainGlobalConfig() {
//Cargo la configuracion
    xml_document<> doc;
    file<> xmlFile(path.c_str()); //open file
    doc.parse<0>(xmlFile.data());
    xml_node<> *configuracion = doc.first_node("config");
    xml_node<> *ancho = configuracion->first_node("ancho");
    xml_node<> *alto = configuracion->first_node("alto");
    xml_node<> *cant_players = configuracion->first_node("cant_players");

    struct xmlConfig config;
    config.ancho = atoi(ancho->value());
    config.alto = atoi(alto->value());
    config.cant_players = atoi(cant_players->value());

    return config;
}

vector<struct xmlLvl> XmlLoader::obtainLvlsConfig() {
    xml_document<> doc;
    file<> xmlFile(pathLevelsConfig.c_str()); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlLvl> configs;
    vector<struct xmlPlatform> plataformas;
    xml_node<> *lvls = doc.first_node("levels");
    for (xml_node<> *lvl = lvls->first_node("lvl"); lvl; lvl = lvl->next_sibling()) {
        xml_node<> *id = lvl->first_node("id");
        xml_node<> *cant_enemies = lvl->first_node("cant_enemies");
        xml_node<> *cant_boxes = lvl->first_node("cant_boxes");
        xml_node<> *posXtoFinish = lvl->first_node("posXtoFinish");
        xml_node<> *platforms = lvl->first_node("platforms");
        for (xml_node<> *platform = platforms->first_node("platform"); platform; platform = platform->next_sibling()) {
            xml_node<> *x = platform->first_node("x");
            xml_node<> *y = platform->first_node("y");                    
            xml_node<> *ancho = platform->first_node("ancho");
            xml_node<> *alto = platform->first_node("alto");

            struct xmlPlatform platfrm;
            platfrm.x = atoi(x->value());
            platfrm.y = atoi(y->value());
            platfrm.ancho = atoi(ancho->value());
            platfrm.alto = atoi(alto->value());

            plataformas.push_back(platfrm);
        }

        struct xmlLvl lvlConfig;
        lvlConfig.completion = EventCompletion::PARTIAL_MSG;
        lvlConfig.id = atoi(id->value());
        lvlConfig.cant_enemies = atoi(cant_enemies->value());
        lvlConfig.cant_boxes = atoi(cant_boxes->value());
        lvlConfig.posXtoFinish = atoi(posXtoFinish->value());
        lvlConfig.platforms = plataformas;

        configs.push_back(lvlConfig);
    }
    configs.back().completion = EventCompletion::FINAL_MSG;
    return configs;
}
