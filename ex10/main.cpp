#include "../include/Matrix.hpp"

// ex10: reduced row-echelon form. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Matrix<float> a = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nexpected: [[1, 0, 0], [0, 1, 0], [0, 0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[1, 2], [3, 4]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {2, 4}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[1, 2], [2, 4]]\nexpected: [[1, 2], [0, 0]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{8, 5, -2, 4, 28}, {4, 2.5, 20, 4, -4}, {8, 5, 1, 4, 17}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[8, 5, -2, 4, 28], [4, 2.5, 20, 4, -4], [8, 5, 1, 4, 17]]\n"
                    << "expected: [[1, 0.625, 0, 0, -12.1667], [0, 0, 1, 0, -3.66667], [0, 0, 0, 1, 29.5]]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[0, 0], [0, 0]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[1, 0], [0, 1]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{4, 2}, {2, 1}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[4, 2], [2, 1]]\nexpected: [[1, 0.5], [0, 0]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{-7, 2}, {4, 8}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[-7, 2], [4, 8]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{1, 2}, {4, 8}}; Matrix<float> r = a.row_echelon();
          std::cout << "input:    [[1, 2], [4, 8]]\nexpected: [[1, 2], [0, 0]]\nresult:\n" << r << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
