#include "XmlLoader.h"

using namespace std;
using namespace rapidxml;

XmlLoader::XmlLoader() {}

XmlLoader::~XmlLoader() {}

void XmlLoader::loadXML(){
	xml_document<> doc;
	file<> xmlFile("config.xml"); //open file
	doc.parse<0>(xmlFile.data()); //parse the contents of file

	//Cargo la configuracion
	xml_node<>* configuracion = doc.first_node("ventana");
		xml_node<>* ancho = configuracion->first_node("ancho");
		xml_node<>* alto = configuracion->first_node("alto");
		xml_node<>* cant_players = configuracion->first_node("cant_players");
	cout << ancho->value() << endl;
	cout << alto->value() << endl;

	//Cargo los sprites
	xml_node<>* sprites = doc.first_node("sprites");
		for(xml_node<>* sprite = sprites->first_node("sprite"); sprite ; sprite = sprite->next_sibling()){

			xml_node<>* id = sprite->first_node("id");
			xml_node<>* path = sprite->first_node("path");
			xml_node<>* ancho = sprite->first_node("ancho");
			xml_node<>* alto = sprite->first_node("alto");
			xml_node<>* speed = sprite->first_node("speed");

			cout << id->value() << endl;
			cout << path->value() << endl;
			cout << ancho->value() << endl;
			cout << alto->value() << endl;
			cout << speed->value() << endl;
		}

	//Cargo los sprites de backgrounds
	xml_node<>* backgrounds = doc.first_node("backgrounds");

	for(xml_node<>* background = backgrounds->first_node("background"); background ; background = background->next_sibling()){
		xml_node<>* id = background->first_node("id");
		xml_node<>* imagen_fondo = background->first_node("imagen_fondo");
		xml_node<>* ancho = background->first_node("ancho");
		xml_node<>* alto = background->first_node("alto");
		xml_node<>* zindex = background->first_node("zindex");

		cout << imagen_fondo->value() << endl;
		cout << ancho->value() << endl;
		cout << zindex->value() << endl;
	}

}

