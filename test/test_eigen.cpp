#include <iostream>
#include <string>
#include "Eigen/Eigen"

void test_basic_matrix() {
    Eigen::Matrix3d m = Eigen::Matrix3d::Random();// try a random matrix
    std::cout << "Generate a random 3*3 matrix M =" << std::endl
              << m << std::endl;
    std::cout << "Here is m.sum():       " << m.sum() << std::endl;
    std::cout << "Here is m.prod():      " << m.prod() << std::endl;
    std::cout << "Here is m.mean():      " << m.mean() << std::endl;
    std::cout << "Here is m.minCoeff():  " << m.minCoeff() << std::endl;
    std::cout << "Here is m.maxCoeff():  " << m.maxCoeff() << std::endl;
    std::cout << "Here is m.trace():     " << m.trace() << std::endl;

    Eigen::VectorXd v = Eigen::VectorXd::Random(3);// try a random vector
    std::cout << "Generate a random vector V =" << std::endl << v << std::endl;
    std::cout << "M * V =" << std::endl << (m * v) << std::endl;

    Eigen::Matrix4i x {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}
    }; //generate a 4x4 interger matrix
    std::cout << "Generate a " << x.rows() << "x" << x.cols() << " matrix:" << std::endl;
    std::cout << x << std::endl;
}

void test_array() {
    Eigen::Array22f a1 = Eigen::Array4f::LinSpaced(0.0, 3.0).reshaped(2, 2);
    std::cout << "Generate an array:" << std::endl << a1 << std::endl;

    Eigen::Array22f a2{
        {1.0f, 0.2f}, {3.1f, 3.2f}
    };
    std::cout << "Second array:" << std::endl << a2 << std::endl;
    std::cout << "Element-wise product a1 * a2 =" << std::endl << a1 * a2 << std::endl;
    std::cout << "Change to matrices and get product:" << std::endl
              << a1.matrix() * a2.matrix() << std::endl;
}

int main() {
    std::cout << "Hello Eigen" << std::endl << std::endl;

    test_basic_matrix();
    std::cout << std::endl;

    test_array();
    std::cout << std::endl;

    return 0;
}
