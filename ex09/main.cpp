#include "../include/Matrix.hpp"

// ex09: transpose. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Examples ==========\n";
        { Matrix<float> a = {{1, 0}, {0, 1}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, -5, 0}, {4, 3, 7}, {-2, 3, 4}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[2, -5, 0], [4, 3, 7], [-2, 3, 4]]\nexpected: [[2, 4, -2], [-5, 3, 3], [0, 7, 4]]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[0, 0], [0, 0]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: [[1, 3], [2, 4]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}, {5, 6}}; Matrix<float> r = a.transpose();
          std::cout << "input:    [[1, 2], [3, 4], [5, 6]]   (3 x 2)\nexpected: [[1, 3, 5], [2, 4, 6]]   (2 x 3)\nresult:\n" << r << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
