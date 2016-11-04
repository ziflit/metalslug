#include "XmlLoader.h"

XmlLoader::XmlLoader(string path) {
    this->path = path;
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
        else if ("BACKGROUND_Z0" == id) {
            return BACKGROUND_Z0;
        }
        else if ("BACKGROUND_Z1" == id) {
            return BACKGROUND_Z1;
        }
        else if ("BACKGROUND_Z2" == id) {
            return BACKGROUND_Z2;
        }
        else if ("BACKGROUND_Z3" == id) {
            return BACKGROUND_Z3;
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

