#include "../include/Vector.hpp"

// ex05: cosine of the angle between two vectors. Each test prints the input, the expected result, then the result.
// "swapped" runs the same pair the other way round: the answer must not change.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Vector<float> u = {1, 0}; Vector<float> v = {1, 0}; float r = angle_cos(u, v);
          std::cout << "input:    [1, 0] and [1, 0]\nexpected: 1\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 0}; Vector<float> v = {0, 1}; float r = angle_cos(u, v);
          std::cout << "input:    [1, 0] and [0, 1]\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {-1, 1}; Vector<float> v = {1, -1}; float r = angle_cos(u, v);
          std::cout << "input:    [-1, 1] and [1, -1]\nexpected: -1\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {2, 1}; Vector<float> v = {4, 2}; float r = angle_cos(u, v);
          std::cout << "input:    [2, 1] and [4, 2]\nexpected: 1\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {1, 2, 3}; Vector<float> v = {4, 5, 6}; float r = angle_cos(u, v);
          std::cout << "input:    [1, 2, 3] and [4, 5, 6]\nexpected: 0.974632\nresult:   " << r << "\n\n"; }

        std::cout << "========== More inputs, each one also swapped ==========\n";
        { Vector<float> u = {8, 7}; Vector<float> v = {3, 2}; float r = angle_cos(u, v); float s = angle_cos(v, u);
          std::cout << "input:    [8, 7] and [3, 2]\nexpected: 0.991454 (same when swapped)\nresult:   " << r << ", swapped: " << s << "\n\n"; }
        { Vector<float> u = {1, 1}; Vector<float> v = {1, 1}; float r = angle_cos(u, v); float s = angle_cos(v, u);
          std::cout << "input:    [1, 1] and [1, 1]\nexpected: 1 (same when swapped)\nresult:   " << r << ", swapped: " << s << "\n\n"; }
        { Vector<float> u = {4, 2}; Vector<float> v = {1, 1}; float r = angle_cos(u, v); float s = angle_cos(v, u);
          std::cout << "input:    [4, 2] and [1, 1]\nexpected: 0.948683 (same when swapped)\nresult:   " << r << ", swapped: " << s << "\n\n"; }
        { Vector<float> u = {-7, 3}; Vector<float> v = {6, 4}; float r = angle_cos(u, v); float s = angle_cos(v, u);
          std::cout << "input:    [-7, 3] and [6, 4]\nexpected: -0.546268 (same when swapped)\nresult:   " << r << ", swapped: " << s << "\n\n"; }
        { Vector<float> u = {1, 0}; Vector<float> v = {0, 1}; float r = angle_cos(u, v); float s = angle_cos(v, u);
          std::cout << "input:    [1, 0] and [0, 1]\nexpected: 0 (same when swapped)\nresult:   " << r << ", swapped: " << s << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
