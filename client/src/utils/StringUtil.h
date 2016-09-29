
#ifndef METALSLUG_STRINGUTIL_H
#define METALSLUG_STRINGUTIL_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


class StringUtil {
private:
public:

    vector<string> split(const string &s, char delimiter);

private:
    void split(const string &s, char delimiter, vector<string> &elems);
};


#endif //METALSLUG_STRINGUTIL_H
