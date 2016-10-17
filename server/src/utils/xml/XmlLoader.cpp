#include "XmlLoader.h"


XmlLoader::XmlLoader() {}

XmlLoader::~XmlLoader() {}


vector<struct xmlBackground> XmlLoader::obtainBackgroundsConfig() {
    xml_document<> doc;
    file<> xmlFile("config.xml"); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlBackground> configs;
    xml_node<> *backgrounds = doc.first_node("backgrounds");

    for (xml_node<> *background = backgrounds->first_node(
            "background"); background; background = background->next_sibling()) {
        xml_node<> *id = background->first_node("id");
        xml_node<> *imagen_fondo = background->first_node("imagen_fondo");
        xml_node<> *ancho = background->first_node("ancho");
        xml_node<> *alto = background->first_node("alto");
        xml_node<> *zindex = background->first_node("zindex");

        struct xmlBackground backgroundConfig;
        backgroundConfig.id = id->value();
        backgroundConfig.ancho = atoi(ancho->value());
        backgroundConfig.alto = atoi(alto->value());
        backgroundConfig.path = imagen_fondo->value();
        backgroundConfig.zindex = atoi(zindex->value());

        configs.push_back(backgroundConfig);
    }
    return configs;
}

vector<struct xmlPlayer> XmlLoader::getSpritesConfig() {
//Cargo los sprites
    xml_document<> doc;
    file<> xmlFile("config.xml"); //open file
    doc.parse<0>(xmlFile.data());
    vector<struct xmlPlayer> configs;
    xml_node<> *sprites = doc.first_node("sprites");
    for (xml_node<> *sprite = sprites->first_node("sprite"); sprite; sprite = sprite->next_sibling()) {
        xml_node<> *id = sprite->first_node("id");
        xml_node<> *path = sprite->first_node("path");
        xml_node<> *ancho = sprite->first_node("ancho");
        xml_node<> *alto = sprite->first_node("alto");
        xml_node<> *speed = sprite->first_node("speed");

        struct xmlPlayer playerConfig;
        playerConfig.id = id->value();
        playerConfig.path = path->value();
        playerConfig.ancho = atoi(ancho->value());
        playerConfig.alto = atoi(alto->value());
        playerConfig.speed = atoi(speed->value());

        configs.push_back(playerConfig);
    }
    return configs;
}

struct xmlConfig XmlLoader::obtainGlobalConfig() {
//Cargo la configuracion
    xml_document<> doc;
    file<> xmlFile("config.xml"); //open file
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


