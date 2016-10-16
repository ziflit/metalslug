#include "XmlLoader.h"

using namespace std;
using namespace rapidxml;

XmlLoader::XmlLoader() {


}

XmlLoader::~XmlLoader() {

}

void XmlLoader::loadXML(){

	xml_document<> doc;
	file<> xmlFile("../../../config.xml"); //open file
	doc.parse<0>(xmlFile.data()); //parse the contents of file

	xml_node<>* ventana = doc.first_node("ventana");
	xml_node<>* ancho = ventana->first_node("ancho");
	xml_node<>* alto = ventana->first_node("alto");
	cout << ancho->value() << endl;
	cout << alto->value() << endl;

	xml_node<>* sprites = doc.first_node("sprites");

	for(xml_node<>* sprite = sprites->first_node("sprite"); sprite ; sprite = sprite->next_sibling()){

		xml_node<>* id = sprite->first_node("id");
		xml_node<>* path = sprite->first_node("path");
		xml_node<>* ancho = sprite->first_node("ancho");
		xml_node<>* alto = sprite->first_node("alto");
		xml_node<>* zindex = sprite->first_node("alto");

		cout << id->value() << endl;
		cout << path->value() << endl;
		cout << ancho->value() << endl;
		cout << alto->value() << endl;
		cout << zindex->value() << endl;
	}
	xml_node<>* capas = doc.first_node("capas");

	for(xml_node<>* capa = capas->first_node("capa"); capa ; capa = capa->next_sibling()){

		xml_node<>* imagen_fondo = capa->first_node("imagen_fondo");
		xml_node<>* ancho = capa->first_node("ancho");
		xml_node<>* zindex = capa->first_node("zindex");

		cout << imagen_fondo->value() << endl;
		cout << ancho->value() << endl;
		cout << zindex->value() << endl;
	}

}

