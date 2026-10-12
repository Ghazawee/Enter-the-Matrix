#include "../include/Matrix.hpp"

// ex13: rank. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; size_t r = a.rank();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: 3\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 2, 0, 0}, {2, 4, 0, 0}, {-1, 2, 1, 1}}; size_t r = a.rank();
          std::cout << "input:    [[1, 2, 0, 0], [2, 4, 0, 0], [-1, 2, 1, 1]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}, {21, 18, 7}}; size_t r = a.rank();
          std::cout << "input:    [[8, 5, -2], [4, 7, 20], [7, 6, 1], [21, 18, 7]]\nexpected: 3\nresult:   " << r << "\n\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; size_t r = a.rank();
          std::cout << "input:    [[0, 0], [0, 0]]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; size_t r = a.rank();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{2, 0}, {0, 2}}; size_t r = a.rank();
          std::cout << "input:    [[2, 0], [0, 2]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 1}, {1, 1}}; size_t r = a.rank();
          std::cout << "input:    [[1, 1], [1, 1]]\nexpected: 1\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{0, 1}, {1, 0}}; size_t r = a.rank();
          std::cout << "input:    [[0, 1], [1, 0]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; size_t r = a.rank();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Matrix<float> a = {{-7, 5}, {4, 6}}; size_t r = a.rank();
          std::cout << "input:    [[-7, 5], [4, 6]]\nexpected: 2\nresult:   " << r << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
