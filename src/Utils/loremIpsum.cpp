#include "loremIpsum.h"

using namespace std;

LoremIpsum::LoremIpsum(long freq, long cant_max, char* path, Client* client){

	this->freq = freq;
	this->cant_max = cant_max;
	this->path = path;
	this->client = client;

}


int msgSender(long cant, int randUser, vector<string> contentMsgList, Client* client, int longContent, int posToStartReading, int MsgListSize ){
	for( long i = 0 ; i < cant ; ++i ){
		if (posToStartReading >= MsgListSize){
			posToStartReading = 0;
		} 
		client->send_message(randUser, contentMsgList[posToStartReading]);
		posToStartReading = posToStartReading + 1;
	}
	return posToStartReading;
}


vector<string> loadFileToMsgList(int lenghtOfString){
	vector<string> contentMsgList;
	string actual;
    
	char b[lenghtOfString] = "";
	ifstream f("src/Utils/arch.txt");
	f.seekg(0, f.end);
	int file_size = (int)f.tellg();
	f.seekg(0, f.beg);

	while ( ( (int)f.tellg() + lenghtOfString) <= file_size){
		f.read(b, sizeof(b) - 1); 
		actual.assign(b);
		contentMsgList.push_back(actual);
	}

	if ( ( (int)f.tellg() + lenghtOfString ) > file_size ){
		char c[file_size - (int)f.tellg()] = "";
		f.read(c, sizeof(c) - 1); 
		actual.assign(c);
		contentMsgList.push_back(actual);
	}

	return contentMsgList;
}


void LoremIpsum::iniciar(){
	/* Elijo un usuario random */
	srand(time(NULL)); 
	int randUser = rand() % ( client->sizeofUserList() - 1 ); 
	int randomChar = rand()%(200-1)+1;
	int posToStartReading = 0;
	long cant_enviados = 0, cant_restante, cant_enviados_actual;
	vector<string> contentMsgList = loadFileToMsgList(randomChar);
	int MsgListSize = contentMsgList.size();
	chrono::seconds interval(1) ; // Para esperar 1 segundo

	while ( cant_enviados < cant_max ){
		if ( cant_enviados + freq >= cant_max ){
			cant_enviados_actual = cant_max - cant_enviados;
		} else {
			cant_enviados_actual = freq;
		}

		posToStartReading = msgSender(cant_enviados_actual, randUser, contentMsgList, client, randomChar, posToStartReading, MsgListSize );
		this_thread::sleep_for(interval);
		cant_enviados = cant_enviados + cant_enviados_actual;

	}

}






