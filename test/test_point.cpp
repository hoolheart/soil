#include "soil/geo/point.hpp"
#include <algorithm> // for std::copy
#include <iostream>
#include <iterator> // for std::ostream_iterator
#include <typeinfo>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    if (!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

int main() {
    std::cout << "Test point of geo submodule" << std::endl << std::endl;

    std::cout << "Create a point by using default constructor: ";
    soil::geo::Point<double, 5> p0;
    for (size_t i=0; i<p0.dimension(); ++i) {
        std::cout << p0[i] << ", ";
        p0[i] = i * 0.1 + 0.1;
    }
    std::cout << std::endl;
    std::cout << "After setting: " << p0.to_vector() << std::endl << std::endl;

    auto p1 = p0.as<float>();
    std::cout << "Change type to " << typeid(p1.x()).name() << std::endl;
    p1.y(55.1f);
    std::cout << "Second element is changed to " << p1.y() << std::endl << std::endl;

    soil::geo::FPoint3D p2(p1.to_vector());
    std::cout << "Constructor 3D point by using vector: ";
    for (size_t i = 0; i < p2.dimension(); ++i) {
        std::cout << p2.at(i) << ", ";
    }
    std::cout << std::endl << std::endl;

    soil::geo::I32Point2D p3({76, 18});
    std::cout << "Constructor 2D integer point: ";
    auto ptr = p3.ptr();
    for (size_t i = 0; i < p3.dimension(); ++i) {
        std::cout << ptr[i] << ", ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}
