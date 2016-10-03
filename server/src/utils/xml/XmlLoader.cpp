/*
 * XmlLoader.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "XmlLoader.h"

using namespace std;
using namespace rapidxml;

XmlLoader::XmlLoader() {
	// TODO Auto-generated constructor stub

}

XmlLoader::~XmlLoader() {
	// TODO Auto-generated destructor stub
}

//TODO: Hacer que lea el XML posta -------
void XmlLoader::loadXML(){
	xml_document<> doc;
	file<> xmlFile("../../config.xml"); //open file
	doc.parse<0>(xmlFile.data()); //parse the contents of file

	xml_node<>* root = doc.first_node("ventana");
	for(xml_node<>* cd = root->first_node("CD"); cd ; cd=cd->next_sibling()){

		xml_node<>* title = cd->first_node("TITULO");
		xml_node<>* artist = cd->first_node("ARTISTA");
		xml_node<>* origen = cd->first_node("ORIGEN");
		xml_node<>* precio = cd->first_node("PRECIO");
		xml_node<>* ano = cd->first_node("ANO");
		cout << title->value() << "\n";
		cout << artist->value() << "\n"; //print node1 value
		cout << origen->value() << "\n";
		cout << precio->value() << "\n";
		cout << ano->value() << "\n";

	}
}
