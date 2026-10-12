#include "../include/Vector.hpp"
#include "../include/Matrix.hpp"

// ex00: add, sub, scl on vectors and matrices. Each test prints the input, the expected result, then the result.
// add, sub and scl change the object itself, so the result is the object after the call.

int main() {
    try {
        std::cout << "========== Vector add ==========\n";
        { Vector<float> u = {0, 0}; u.add({0, 0});
          std::cout << "input:    [0, 0] + [0, 0]\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 0}; u.add({0, 1});
          std::cout << "input:    [1, 0] + [0, 1]\nexpected: [1, 1]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 1}; u.add({1, 1});
          std::cout << "input:    [1, 1] + [1, 1]\nexpected: [2, 2]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {21, 21}; u.add({21, 21});
          std::cout << "input:    [21, 21] + [21, 21]\nexpected: [42, 42]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {-21, 21}; u.add({21, -21});
          std::cout << "input:    [-21, 21] + [21, -21]\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; u.add({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
          std::cout << "input:    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] + [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]\nexpected: ten 9s\nresult:\n" << u << "\n"; }

        std::cout << "========== Vector sub ==========\n";
        { Vector<float> u = {0, 0}; u.sub({0, 0});
          std::cout << "input:    [0, 0] - [0, 0]\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 0}; u.sub({0, 1});
          std::cout << "input:    [1, 0] - [0, 1]\nexpected: [1, -1]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 1}; u.sub({1, 1});
          std::cout << "input:    [1, 1] - [1, 1]\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {21, 21}; u.sub({21, 21});
          std::cout << "input:    [21, 21] - [21, 21]\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {-21, 21}; u.sub({21, -21});
          std::cout << "input:    [-21, 21] - [21, -21]\nexpected: [-42, 42]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; u.sub({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
          std::cout << "input:    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] - [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]\nexpected: [-9, -7, -5, -3, -1, 1, 3, 5, 7, 9]\nresult:\n" << u << "\n"; }

        std::cout << "========== Vector scl ==========\n";
        { Vector<float> u = {0, 0}; u.scl(1);
          std::cout << "input:    [0, 0] * 1\nexpected: [0, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 0}; u.scl(1);
          std::cout << "input:    [1, 0] * 1\nexpected: [1, 0]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {1, 1}; u.scl(2);
          std::cout << "input:    [1, 1] * 2\nexpected: [2, 2]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {21, 21}; u.scl(2);
          std::cout << "input:    [21, 21] * 2\nexpected: [42, 42]\nresult:\n" << u << "\n"; }
        { Vector<float> u = {42, 42}; u.scl(0.5);
          std::cout << "input:    [42, 42] * 0.5\nexpected: [21, 21]\nresult:\n" << u << "\n"; }

        std::cout << "========== Matrix add ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; a.add({{0, 0}, {0, 0}});
          std::cout << "input:    [[0, 0], [0, 0]] + [[0, 0], [0, 0]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; a.add({{0, 0}, {0, 0}});
          std::cout << "input:    [[1, 0], [0, 1]] + [[0, 0], [0, 0]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 1}, {1, 1}}; a.add({{1, 1}, {1, 1}});
          std::cout << "input:    [[1, 1], [1, 1]] + [[1, 1], [1, 1]]\nexpected: [[2, 2], [2, 2]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{21, 21}, {21, 21}}; a.add({{21, 21}, {21, 21}});
          std::cout << "input:    [[21, 21], [21, 21]] + [[21, 21], [21, 21]]\nexpected: [[42, 42], [42, 42]]\nresult:\n" << a << "\n"; }

        std::cout << "========== Matrix sub ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; a.sub({{0, 0}, {0, 0}});
          std::cout << "input:    [[0, 0], [0, 0]] - [[0, 0], [0, 0]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; a.sub({{0, 0}, {0, 0}});
          std::cout << "input:    [[1, 0], [0, 1]] - [[0, 0], [0, 0]]\nexpected: [[1, 0], [0, 1]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 1}, {1, 1}}; a.sub({{1, 1}, {1, 1}});
          std::cout << "input:    [[1, 1], [1, 1]] - [[1, 1], [1, 1]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{21, 21}, {21, 21}}; a.sub({{21, 21}, {21, 21}});
          std::cout << "input:    [[21, 21], [21, 21]] - [[21, 21], [21, 21]]\nexpected: [[0, 0], [0, 0]]\nresult:\n" << a << "\n"; }

        std::cout << "========== Matrix scl ==========\n";
        { Matrix<float> a = {{0, 0}, {0, 0}}; a.scl(0);
          std::cout << "input:    [[0, 0], [0, 0]] * 0\nexpected: [[0, 0], [0, 0]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 0}, {0, 1}}; a.scl(1);
          std::cout << "input:    [[1, 0], [0, 1]] * 1\nexpected: [[1, 0], [0, 1]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{1, 2}, {3, 4}}; a.scl(2);
          std::cout << "input:    [[1, 2], [3, 4]] * 2\nexpected: [[2, 4], [6, 8]]\nresult:\n" << a << "\n"; }
        { Matrix<float> a = {{21, 21}, {21, 21}}; a.scl(0.5);
          std::cout << "input:    [[21, 21], [21, 21]] * 0.5\nexpected: [[10.5, 10.5], [10.5, 10.5]]\nresult:\n" << a << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
