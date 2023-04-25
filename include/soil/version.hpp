#ifndef SOIL_VERSION_HPP
#define SOIL_VERSION_HPP

#include <string>
#include "soil_export.h"

/** version information of soil */
class SOIL_EXPORT SoilVersion {
public:
    static int Major();
    static int Minor();
    static int Patch();
    static std::string get();
};

#endif // SOIL_VERSION_HPP
