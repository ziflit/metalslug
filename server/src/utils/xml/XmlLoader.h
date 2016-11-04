/*
 * XmlLoader.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_UTILS_XMLLOADER_H_
#define SRC_UTILS_XMLLOADER_H_

#include "../Protocol.h"
#include <iostream>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string.h>

using namespace std;
using namespace rapidxml;

class XmlLoader {
private:
    string path;
public:

    XmlLoader(string path);

    virtual ~XmlLoader();

    struct xmlConfig obtainGlobalConfig();

    vector<struct xmlPlayer> obtainPlayersConfig();

    vector<struct xmlEnemy> obtainEnemiesConfig();

    vector<struct xmlBackground> obtainBackgroundsConfig();

    Entity convertToEntity(string id);
};

#endif /* SRC_UTILS_XMLLOADER_H_ */
