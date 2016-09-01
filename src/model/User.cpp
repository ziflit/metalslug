
#include "User.h"

const string &User::getUsername() const {
    return username;
}

void User::setUsername(const string &username) {
    User::username = username;
}

const string &User::getPassword() const {
    return password;
}

void User::setPassword(const string &password) {
    User::password = password;
}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}
