#include "soil/version.hpp"
#include "config.h"

int SoilVersion::Major() { return PROJ_VER_MAJOR; }

int SoilVersion::Minor() { return PROJ_VER_MINOR; }

int SoilVersion::Patch() { return PROJ_VER_PATCH; }

std::string SoilVersion::get() { return std::string(PROJ_VER); }
