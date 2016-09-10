#include <iostream>
#include <stdlib.h>
#include "loremIpsum.h"
#include <time.h>

using namespace std;

LoremIpsum::LoremIpsum(int freq, int cant_max, char* path, Client* client){

	this-> freq = freq;
	this-> cant_max = cant_max;
	this-> path = path;
	this-> client = client;

}

void LoremIpsum::iniciar(){

	int envios = 1;
	fstream file;
	file.open(path,fstream::in);
	if(file.fail())
		cerr << "Error al abrir el archivo" << endl;

	while(envios < cant_max){

		string message;
		getline(file,message);

		/*
		srand(time(NULL));
		int num =  num = 1 + rand() % (11- 1); //cambiar 11 por el tamaño de la lilsta
		client->send_message_to(num);
		*/

		cout << message << endl;
		envios ++;

		if (file.eof()){
			file.close();
			file.open(path,fstream::in);
		}
	}

	file.close();

}

