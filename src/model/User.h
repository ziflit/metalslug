#ifndef METALSLUG_USER_H
#define METALSLUG_USER_H

#include <string.h>
#include <string>

//se tiene qu sacar
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//-------

using namespace std;

class User {
private:
    char username[20];
    char password[20];
    int id;

public:
    void setUsername(string name);
    
    void setPassword(string pass);
    
    char* getUsername();

    char* getPassword();

    int getId() const;

    void setId(int id);

    bool isMyUsername(char* username);

    bool isMyPassword(char *password);
};


#endif //METALSLUG_USER_H
