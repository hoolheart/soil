#include <iostream>
#include "soil/version.hpp"

int main() {
    std::cout << "Hello Soil V" << SoilVersion::get() << std::endl;
    return 0;
}
