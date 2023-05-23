#ifndef SOIL_VERSION_HPP
#define SOIL_VERSION_HPP

#include <string>
#include "soil_export.h"

namespace soil {

/** version information of soil */
class SOIL_EXPORT Version {
public:
    static int Major();
    static int Minor();
    static int Patch();
    static std::string get();
};

} // namespace soil

#endif // SOIL_VERSION_HPP
