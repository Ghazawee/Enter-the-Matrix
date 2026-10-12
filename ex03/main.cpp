#include "../include/Vector.hpp"

// ex03: dot product. Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Vector<float> u = {0, 0}; Vector<float> v = {1, 1}; float r = u.dot(v);
          std::cout << "input:    [0, 0] . [1, 1]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 1}; Vector<float> v = {1, 1}; float r = u.dot(v);
          std::cout << "input:    [1, 1] . [1, 1]\nexpected: 2\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {-1, 6}; Vector<float> v = {3, 2}; float r = u.dot(v);
          std::cout << "input:    [-1, 6] . [3, 2]\nexpected: 9\nresult:   " << r << "\n\n"; }

        std::cout << "========== More inputs ==========\n";
        { Vector<float> u = {0, 0}; Vector<float> v = {0, 0}; float r = u.dot(v);
          std::cout << "input:    [0, 0] . [0, 0]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 0}; Vector<float> v = {0, 0}; float r = u.dot(v);
          std::cout << "input:    [1, 0] . [0, 0]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 0}; Vector<float> v = {1, 0}; float r = u.dot(v);
          std::cout << "input:    [1, 0] . [1, 0]\nexpected: 1\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 0}; Vector<float> v = {0, 1}; float r = u.dot(v);
          std::cout << "input:    [1, 0] . [0, 1]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {4, 2}; Vector<float> v = {2, 1}; float r = u.dot(v);
          std::cout << "input:    [4, 2] . [2, 1]\nexpected: 10\nresult:   " << r << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
