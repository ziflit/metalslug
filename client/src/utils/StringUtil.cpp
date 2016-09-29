#include "StringUtil.h"

void StringUtil::split(const string &s, char delimiter, vector<string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        elems.push_back(item);
    }
}

vector<string> StringUtil::split(const string &s, char delimiter) {
    vector<string> elems;
    split(s, delimiter, elems);
    return elems;
}

