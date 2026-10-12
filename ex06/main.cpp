#include "../include/Vector.hpp"

// ex06: cross product (3D vectors only). Each test prints the input, the expected result, then the result.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Vector<float> u = {0, 0, 1}; Vector<float> v = {1, 0, 0}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [0, 0, 1] x [1, 0, 0]\nexpected: [0, 1, 0]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {1, 2, 3}; Vector<float> v = {4, 5, 6}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [1, 2, 3] x [4, 5, 6]\nexpected: [-3, 6, -3]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {4, 2, -3}; Vector<float> v = {-2, -5, 16}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [4, 2, -3] x [-2, -5, 16]\nexpected: [17, -58, -16]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs ==========\n";
        { Vector<float> u = {0, 0, 0}; Vector<float> v = {0, 0, 0}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [0, 0, 0] x [0, 0, 0]\nexpected: [0, 0, 0]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {1, 0, 0}; Vector<float> v = {0, 0, 0}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [1, 0, 0] x [0, 0, 0]\nexpected: [0, 0, 0]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {1, 0, 0}; Vector<float> v = {0, 1, 0}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [1, 0, 0] x [0, 1, 0]\nexpected: [0, 0, 1]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {1, 1, 1}; Vector<float> v = {0, 0, 0}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [1, 1, 1] x [0, 0, 0]\nexpected: [0, 0, 0]\nresult:\n" << r << "\n"; }
        { Vector<float> u = {1, 1, 1}; Vector<float> v = {1, 1, 1}; Vector<float> r = cross_product(u, v);
          std::cout << "input:    [1, 1, 1] x [1, 1, 1]\nexpected: [0, 0, 0]\nresult:\n" << r << "\n"; }

        std::cout << "========== The result is perpendicular to both inputs (dot product 0) ==========\n";
        { Vector<float> u = {8, 7, -4}; Vector<float> v = {3, 2, 1}; Vector<float> r = cross_product(u, v);
          float with_u = r.dot(u); float with_v = r.dot(v);
          std::cout << "input:    [8, 7, -4] x [3, 2, 1]\nexpected: [15, -20, -5]\nresult:\n" << r;
          std::cout << "result . [8, 7, -4], expected 0: " << with_u << "\n";
          std::cout << "result . [3, 2, 1], expected 0:  " << with_v << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
