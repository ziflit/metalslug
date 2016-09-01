#ifndef METALSLUG_USER_H
#define METALSLUG_USER_H

#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    int id;

public:
    User(string username,string password, int id);

    const string &getUsername() const;

    void setUsername(const string &username);

    const string &getPassword() const;

    void setPassword(const string &password);

    int getId() const;

    void setId(int id);
};


#endif //METALSLUG_USER_H
