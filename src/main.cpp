#include <iostream>
#include "Utils/File.h"
#include "Utils/StringUtil.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "Hello world!" << std::endl;
    string path = "notas/20160826.txt";
    File *file = new File(path, std::fstream::in);
    cout << file->getSize() << endl;
    file->read();
    StringUtil *sUtil = new StringUtil();
    vector<string> v = sUtil->split("aa;aa", ';');
    for (string elem : v ) {
        cout << elem << endl;
    }


}
