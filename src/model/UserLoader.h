//
//  UserLoader.h
//  UserLoader
//


#ifndef UserLoader_h
#define UserLoader_h

#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class UserLoader {
private:
    vector<User*> usersList;
    
public:
    
    UserLoader();
    
    bool processCSV();
    
    bool isPasswordOk(char* username, char* password);

    unsigned int usersRegistered();

    string getUsersList();
};





#endif /* UserLoader_h */
