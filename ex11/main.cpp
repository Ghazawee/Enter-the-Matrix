#include "../include/Matrix.hpp"

// ex11: determinant. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Matrix<float> a = {{1, -1}, {-1, 1}}; float d = a.determinant();
          std::cout << "input:    [[1, -1], [-1, 1]]\nexpected: 0\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}; float d = a.determinant();
          std::cout << "input:    [[2, 0, 0], [0, 2, 0], [0, 0, 2]]\nexpected: 8\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}}; float d = a.determinant();
          std::cout << "input:    [[8, 5, -2], [4, 7, 20], [7, 6, 1]]\nexpected: -174\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{8, 5, -2, 4}, {4, 2.5, 20, 4}, {8, 5, 1, 4}, {28, -4, 17, 1}}; float d = a.determinant();
          std::cout << "input:    [[8, 5, -2, 4], [4, 2.5, 20, 4], [8, 5, 1, 4], [28, -4, 17, 1]]\nexpected: 1032\nresult:   " << d << "\n\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; float d = a.determinant();
          std::cout << "input:    [[0, 0], [0, 0]]\nexpected: 0\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; float d = a.determinant();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: 1\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{2, 0}, {0, 2}}; float d = a.determinant();
          std::cout << "input:    [[2, 0], [0, 2]]\nexpected: 4\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{1, 1}, {1, 1}}; float d = a.determinant();
          std::cout << "input:    [[1, 1], [1, 1]]\nexpected: 0\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{0, 1}, {1, 0}}; float d = a.determinant();
          std::cout << "input:    [[0, 1], [1, 0]]\nexpected: -1\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; float d = a.determinant();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: -2\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{-7, 5}, {4, 6}}; float d = a.determinant();
          std::cout << "input:    [[-7, 5], [4, 6]]\nexpected: -62\nresult:   " << d << "\n\n"; }
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; float d = a.determinant();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: 1\nresult:   " << d << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
