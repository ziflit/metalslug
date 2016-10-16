/*
 * XmlLoader.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_UTILS_XMLLOADER_H_
#define SRC_UTILS_XMLLOADER_H_

#include <iostream>
#include <fstream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <string.h>


class XmlLoader {
public:
	XmlLoader();
	virtual ~XmlLoader();

	void loadXML();
};

#endif /* SRC_UTILS_XMLLOADER_H_ */
