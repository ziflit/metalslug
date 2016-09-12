#ifndef LOREMIPSUM_H
#define LOREMIPSUM_H

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include "../model/client.h"

using namespace std;

class LoremIpsum{

private:

	long freq;
	long cant_max;
	char* path;
	Client* client;

public:

	LoremIpsum(long freq, long cant_max, char* path, Client* client);

	void iniciar();

};

#endif
