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

    /* Para los path de los sprites, notar que se toma como directorio de inicio
     * la carpeta sprite, entonces por ejemplo, para el sprite ubicado en la carpeta
     * sprites/player/marco.gif la ruta que sera dada por el xml sera player/marco.gif  */

    struct xmlConfig obtainGlobalConfig();

    vector<struct xmlPlayer> obtainSpritesConfig();

    vector<struct xmlBackground> obtainBackgroundsConfig();

};

#endif /* SRC_UTILS_XMLLOADER_H_ */
