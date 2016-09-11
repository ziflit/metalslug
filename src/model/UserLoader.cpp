#include "UserLoader.h"

using namespace std;
UserLoader::UserLoader(string path){
    this->processCSV(path);
}

bool UserLoader::processCSV(string path){
    std::fstream file;
    file.open(path,std::fstream::in);
    if(file.fail()){
        std::cout << "File not found!\n";
        return false;
    }
    
    std::istream &input = file;
    std::string csvLine;
    // read every line from the stream
    while( std::getline(input, csvLine) ){
        std::istringstream csvStream(csvLine);
        std::vector<std::string> csvRow;
        std::string csvCol;
        // read every element from the line that is seperated by commas
        // and put it into the vector or strings
        User* newUser = new User();
        std::getline(csvStream, csvCol, ',');
        cout << csvCol <<endl;
        
        newUser->setUsername(csvCol.data());
        
        std::getline(csvStream, csvCol, ',');
        cout << csvCol <<endl;
        newUser->setPassword(csvCol.data());


        this->usersList.push_back(newUser);
    }
    
    return true;
}

bool UserLoader::isPasswordOk(char *username,char *password){
    for(auto it = usersList.begin(); it != usersList.end(); ++it) {
        if((*it)->isMyUsername(username)){return (*it)->isMyPassword(password);}
    }
    return false;
}

unsigned int UserLoader::usersRegistered() {
    return usersList.size();
}

string UserLoader::getUsersList() {
    string users = "";
    std::vector<User*>::iterator it ;
    for(it= this->usersList.begin(); it != (this->usersList.end()-1); ++it) {

        users += (*it)->getUsername();
        users += ",";
    }

    users += (*it)->getUsername();
    return users;
}

