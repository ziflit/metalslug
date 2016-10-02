#ifndef METALSLUG_USER_H
#define METALSLUG_USER_H

#include <string.h>
#include <string>


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

    bool isMyUsername(const char* username);

    bool isMyPassword(char *password);
};


#endif //METALSLUG_USER_H
