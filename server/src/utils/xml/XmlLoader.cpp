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
        } else {
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

vector<struct xmlPlayer> XmlLoader::obtainSpritesConfig() {
//Cargo los sprites
    xml_document<> doc;
    file<> xmlFile(path.c_str()); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlPlayer> configs;
    xml_node<> *sprites = doc.first_node("sprites");
    for (xml_node<> *sprite = sprites->first_node("sprite"); sprite; sprite =
            sprite->next_sibling()) {
        xml_node<> *id = sprite->first_node("id");
        xml_node<> *pathColor = sprite->first_node("pathColor");
        xml_node<> *pathGrey = sprite->first_node("pathGrey");
        xml_node<> *ancho = sprite->first_node("ancho");
        xml_node<> *alto = sprite->first_node("alto");
        xml_node<> *cantWidthFrames = sprite->first_node("cantWidthFrames");
        xml_node<> *cantHeightFrames = sprite->first_node("cantHeightFrames");
        xml_node<> *speed = sprite->first_node("speed");

        struct xmlPlayer playerConfig;
        playerConfig.completion = EventCompletion::PARTIAL_MSG;
        playerConfig.id = this->convertToEntity(id->value());
        strcpy(playerConfig.pathColor, pathColor->value());
        strcpy(playerConfig.pathGrey, pathGrey->value());
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

