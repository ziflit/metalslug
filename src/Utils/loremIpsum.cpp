#include <iostream>
#include <stdlib.h>
#include "loremIpsum.h"

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
		//Message* msg = new Message(10,"to","from",message);
		//Aca habria que mandar el mensaje posta
		cout << message << endl;
		//cliente->send_message(msg);
		envios ++;

		if (file.eof()){
			file.close();
			file.open(path,fstream::in);
		}
	}

	file.close();

}

