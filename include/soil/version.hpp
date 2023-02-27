#ifndef SOIL_VERSION_H
#define SOIL_VERSION_H

#include <string>

class SoilVersion {
public:
    static int Major();
    static int Minor();
    static int Patch();
    static std::string get();
};


#endif // SOIL_VERSION_H
