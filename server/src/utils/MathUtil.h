//
// Created by leandro on 07/11/16.
//

#ifndef SERVER_MATHUTIL_H
#define SERVER_MATHUTIL_H

#include <cmath>

using namespace std;

class MathUtil {
public:
    static float FindDifference(float nr1, float nr2) {
        return abs(nr1 - nr2);
    }
};


#endif //SERVER_MATHUTIL_H
