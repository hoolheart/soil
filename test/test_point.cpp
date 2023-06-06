#include <algorithm> // for std::copy
#include <iostream>
#include <iterator> // for std::ostream_iterator
#include <typeinfo>
#include "soil/geo/point.hpp"

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
    for (size_t i=0; i<p0.size(); ++i) {
        std::cout << p0[i] << ", ";
        p0[i] = i * 0.1 + 0.1;
    }
    std::cout << std::endl;
    std::cout << "After setting: " << soil::geo::to_vector(p0)
              << std::endl << std::endl;

    auto p1 = soil::geo::as<double, float, 5>(p0);
    std::cout << "Change type to " << typeid(p1[0]).name() << std::endl;
    p1[1] = 55.1f;
    std::cout << "Second item changes to " << p1[1] << std::endl << std::endl;

    auto p2 = soil::geo::from_vector<float, 3>(soil::geo::to_vector(p1));
    std::cout << "Constructor 3D point by using vector: " << std::endl
              << p2 << std::endl << std::endl;

    soil::geo::I32Point2D p3({76, 18});
    std::cout << "Constructor 2D integer point: ";
    auto ptr = p3.data();
    for (size_t i = 0; i < p3.size(); ++i) {
        std::cout << ptr[i] << ", ";
    }
    std::cout << std::endl << std::endl;

    auto hp2 = soil::geo::to_homogeneous(p2);
    std::cout << "Homogeneous point of P2: " << std::endl << hp2 << std::endl;
    hp2[3] *= 10.0f;
    std::cout << "Transformed point: " << std::endl
              << soil::geo::from_homogeneous<float, 3>(hp2)
              << std::endl << std::endl;

    return 0;
}
