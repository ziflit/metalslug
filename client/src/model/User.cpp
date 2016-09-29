
#include "User.h"

void User::setUsername(string name){
    
    strcpy(this->username,name.data());
    
}

void User::setPassword(string pass){
    strcpy(this->password,pass.data());
    
}

char* User::getUsername() {
    return username;
}
char* User::getPassword() {
    return password;
}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    this->id = id;
}

bool User::isMyPassword(char *password){

    return ((strcmp(this->password, password) == 0));
}

bool User::isMyUsername(const char *username) {

    return ((strcmp(this->username, username) == 0));
}
