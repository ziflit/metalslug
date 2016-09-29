//
//  UserLoader.h
//  UserLoader
//


#ifndef UserLoader_h
#define UserLoader_h

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "User.h"


using namespace std;

class UserLoader {
private:
    vector<User*> usersList;
    
public:
    UserLoader();

    UserLoader(string path);
    
    bool processCSV(string path);
    
    bool isPasswordOk(char* username, char* password);

    unsigned int usersRegistered();

    string getUsersList();
};





#endif /* UserLoader_h */
