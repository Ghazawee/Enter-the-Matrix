#include "../include/Matrix.hpp"

// ex12: inverse. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[2, 0, 0], [0, 2, 0], [0, 0, 2]]\nexpected: [[0.5, 0, 0], [0, 0.5, 0], [0, 0, 0.5]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[8, 5, -2], [4, 7, 20], [7, 6, 1]]\n"
                    << "expected: [[0.649425, 0.0977011, -0.655172], [-0.781609, -0.126437, 0.965517], [0.143678, 0.0747126, -0.206897]]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{1, 0}, {0, 1}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, 0}, {0, 2}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[2, 0], [0, 2]]\nexpected: [[0.5, 0], [0, 0.5]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{0.5, 0}, {0, 0.5}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[0.5, 0], [0, 0.5]]\nexpected: [[2, 0], [0, 2]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{0, 1}, {1, 0}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[0, 1], [1, 0]]\nexpected: [[0, 1], [1, 0]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; Matrix<float> r = a.inverse();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: [[-2, 1], [1.5, -0.5]]\nresult:\n" << r << "\n"; }

        // A matrix times its inverse gives the identity. Floats keep only about 7 digits, so a result
        // like 1e-07 (= 0.0000001) is a rounding leftover where the exact answer is 0.
        std::cout << "========== Check: A times its inverse is the identity ==========\n";
        { Matrix<float> a = {{1, 2}, {3, 4}}; Matrix<float> r = a.inverse(); Matrix<float> p = a.mul_mat(r);
          std::cout << "input:    [[1, 2], [3, 4]] times its inverse\nexpected: [[1, 0], [0, 1]]   (or very close)\nresult:\n" << p << "\n"; }
        { Matrix<float> a = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}}; Matrix<float> r = a.inverse(); Matrix<float> p = a.mul_mat(r);
          std::cout << "input:    [[8, 5, -2], [4, 7, 20], [7, 6, 1]] times its inverse\nexpected: [[1, 0, 0], [0, 1, 0], [0, 0, 1]]   (or very close)\nresult:\n" << p << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
