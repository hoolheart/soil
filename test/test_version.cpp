#include <iostream>
#include "soil/version.hpp"

int main() {
    std::cout << "Hello Soil V" << soil::Version::get() << std::endl;
    return 0;
}
