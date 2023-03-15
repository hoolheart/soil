#include <iostream>
#include <string>
#include <algorithm>
#include <typeinfo>
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

    for (auto row : m.rowwise()) {
        std::sort(row.begin(), row.end());
    }
    std::cout << "After sorting rowwisely" << std::endl;
    std::cout << m << std::endl;

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

void test_block() {
    Eigen::MatrixXd m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    std::cout << "Generate matrix " << m.rows() << "x" << m.cols() << std::endl;
    for (int i=0; i+2 <= m.rows(); ++i) {
        for (int j=0; j+2 <= m.cols(); ++j) {
            std::cout << "Block at "<< i << ", " << j << std::endl;
            std::cout << m.block<2, 2>(i, j) << std::endl; 
        }
    }
    Eigen::Array33d arr = Eigen::ArrayXd::LinSpaced(9, 1.0, 9.0).reshaped(3, 3);
    std::cout << "Generate array " << arr.rows() << "x" << arr.cols() << std::endl;
    for (int i=0; i+2 <= arr.rows(); ++i) {
        for (int j=0; j+2 <= arr.cols(); ++j) {
            std::cout << "Block at "<< i << ", " << j << std::endl;
            std::cout << arr.block<2, 2>(i, j) << std::endl; 
        }
    }
}

void test_mapper() {
    double raw_data[8] = {0.0};
    for (int i=0; i<8; ++i) {
        raw_data[i] = i / 7.0;
    }
    auto m = Eigen::Map<Eigen::Matrix<double, 2, 4> >(raw_data);
    std::cout << "Generate a " << typeid(m).name() << std::endl;
    std::cout << m << std::endl;
    std::cout << "Use row major:" << std::endl;
    std::cout << Eigen::Map<Eigen::Matrix<double, 2, 4, Eigen::RowMajor> >(raw_data) << std::endl;
}

void test_algebra() {
    Eigen::Matrix2f A{{1.0f, 0.1f}, {-0.32f, 2.0f}};
    Eigen::Vector2f b{0.1f, 0.2f};
    std::cout << "Matrix A" << std::endl << A << std::endl;
    std::cout << "Vecotr b" << std::endl << b << std::endl;
    std::cout << "Solve Ax=b by using QR decomposition with column pivoting" << std::endl;
    auto x = A.colPivHouseholderQr().solve(b);
    std::cout << x << std::endl;
    std::cout << "Residual of solving:" << std::endl << (A * x - b) << std::endl;

    std::cout << "Determinant of A: " << A.determinant() << std::endl;

    Eigen::EigenSolver<Eigen::Matrix2f> eigen_solver(A);
    if (eigen_solver.info() == Eigen::Success) {
        auto eigen_values = eigen_solver.eigenvalues();
        auto eigen_vectors = eigen_solver.eigenvectors();
        for (int i=0; i<eigen_values.rows(); ++i) {
            std::cout << "Eigen value " << i+1 << ": " << eigen_values(i).real() << std::endl;
            std::cout << "Corresponding eigen vector:" << std::endl
                      << eigen_vectors.col(i).real() << std::endl;
        }
    }
    else {
        std::cout << "Failed to solve eigen values" << std::endl;
    }
}

int main() {
    std::cout << "Hello Eigen" << std::endl << std::endl;

    test_basic_matrix();
    std::cout << std::endl;

    test_array();
    std::cout << std::endl;

    test_block();
    std::cout << std::endl;

    test_mapper();
    std::cout << std::endl;

    test_algebra();
    std::cout << std::endl;

    return 0;
}
