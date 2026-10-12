#include "../include/Vector.hpp"
#include "../include/Matrix.hpp"

// ex07: matrix times vector (mul_vec) and matrix times matrix (mul_mat).
// Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples: mul_vec ==========\n";
        { Matrix<float> a = {{1, 0}, {0, 1}}; Vector<float> u = {4, 2}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[1, 0], [0, 1]] times [4, 2]\nexpected: [4, 2]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, 0}, {0, 2}}; Vector<float> u = {4, 2}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[2, 0], [0, 2]] times [4, 2]\nexpected: [8, 4]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, -2}, {-2, 2}}; Vector<float> u = {4, 2}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[2, -2], [-2, 2]] times [4, 2]\nexpected: [4, -4]\nresult:\n" << r << "\n"; }

        std::cout << "========== Subject examples: mul_mat ==========\n";
        { Matrix<float> a = {{1, 0}, {0, 1}}; Matrix<float> b = {{1, 0}, {0, 1}}; Matrix<float> r = a.mul_mat(b);
          std::cout << "input:    [[1, 0], [0, 1]] times [[1, 0], [0, 1]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; Matrix<float> b = {{2, 1}, {4, 2}}; Matrix<float> r = a.mul_mat(b);
          std::cout << "input:    [[1, 0], [0, 1]] times [[2, 1], [4, 2]]\nexpected: [[2, 1], [4, 2]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{3, -5}, {6, 8}}; Matrix<float> b = {{2, 1}, {4, 2}}; Matrix<float> r = a.mul_mat(b);
          std::cout << "input:    [[3, -5], [6, 8]] times [[2, 1], [4, 2]]\nexpected: [[-14, -7], [44, 22]]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs: mul_vec ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; Vector<float> u = {7, -3}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[0, 0], [0, 0]] times [7, -3]\nexpected: [0, 0]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; Vector<float> u = {7, -3}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[1, 0], [0, 1]] times [7, -3]\nexpected: [7, -3]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 1}, {1, 1}}; Vector<float> u = {4, 2}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[1, 1], [1, 1]] times [4, 2]\nexpected: [6, 6]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, 0}, {0, 2}}; Vector<float> u = {2, 1}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[2, 0], [0, 2]] times [2, 1]\nexpected: [4, 2]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{0.5, 0}, {0, 0.5}}; Vector<float> u = {4, 2}; Vector<float> r = a.mul_vec(u);
          std::cout << "input:    [[0.5, 0], [0, 0.5]] times [4, 2]\nexpected: [2, 1]\nresult:\n" << r << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
