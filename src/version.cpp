#include "soil/version.hpp"
#include "config.h"

using namespace soil;

int Version::Major() { return PROJ_VER_MAJOR; }

int Version::Minor() { return PROJ_VER_MINOR; }

int Version::Patch() { return PROJ_VER_PATCH; }

std::string Version::get() { return std::string(PROJ_VER); }
