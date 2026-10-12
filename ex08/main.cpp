#include "../include/Matrix.hpp"

// ex08: trace. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Matrix<float> a = {{1, 0}, {0, 1}}; float r = a.trace();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{2, -5, 0}, {4, 3, 7}, {-2, 3, 4}}; float r = a.trace();
          std::cout << "input:    [[2, -5, 0], [4, 3, 7], [-2, 3, 4]]\nexpected: 9\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{-2, -8, 4}, {1, -23, 4}, {0, 6, 4}}; float r = a.trace();
          std::cout << "input:    [[-2, -8, 4], [1, -23, 4], [0, 6, 4]]\nexpected: -21\nresult:   " << r << "\n\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; float r = a.trace();
          std::cout << "input:    [[0, 0], [0, 0]]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; float r = a.trace();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: 5\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{8, -7}, {4, 2}}; float r = a.trace();
          std::cout << "input:    [[8, -7], [4, 2]]\nexpected: 10\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; float r = a.trace();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: 3\nresult:   " << r << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
