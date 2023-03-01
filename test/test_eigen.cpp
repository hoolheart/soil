#include <iostream>
#include <string>
#include "Eigen/Eigen"

int main() {
    std::cout << "Hello Eigen" << std::endl << std::endl;

    auto m = Eigen::MatrixXd::Random(2, 3);// try a random matrix
    std::cout << "Generate a random 2*3 matrix M" << std::endl
              << m << std::endl << std::endl;

    auto v = Eigen::VectorXd::Random(3);// try a random vector
    std::cout << "Generate a random vector V" << std::endl << v << std::endl;
    std::cout << "M * V =" << std::endl << (m * v) << std::endl << std::endl;

    return 0;
}
