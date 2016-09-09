#ifndef LOREMIPSUM_H
#define LOREMIPSUM_H

#include <fstream>
#include <string.h>
#include <string>
#include "../model/client.h"

using namespace std;

class LoremIpsum{

private:

	int freq;
	int cant_max;
	char* path;
	Client* client;

public:

	LoremIpsum(int freq, int cant_max, char* path, Client* client);

	void iniciar();

};

#endif
