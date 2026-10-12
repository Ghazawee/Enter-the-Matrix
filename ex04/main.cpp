#include "../include/Vector.hpp"

// ex04: the three norms. Each test prints the input, the expected norm_1, norm, norm_inf, then the results.

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { Vector<float> u = {0, 0, 0}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [0, 0, 0]\nexpected: 0, 0, 0\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {1, 2, 3}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [1, 2, 3]\nexpected: 6, 3.74166, 3\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {-1, -2}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [-1, -2]\nexpected: 3, 2.23607, 2\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }

        std::cout << "========== More inputs ==========\n";
        { Vector<float> u = {0}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [0]\nexpected: 0, 0, 0\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {1}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [1]\nexpected: 1, 1, 1\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {0, 0}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [0, 0]\nexpected: 0, 0, 0\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {1, 0}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [1, 0]\nexpected: 1, 1, 1\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {2, 1}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [2, 1]\nexpected: 3, 2.23607, 2\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {4, 2}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [4, 2]\nexpected: 6, 4.47214, 4\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
        { Vector<float> u = {-4, -2}; float n1 = u.norm_1(); float n2 = u.norm(); float ni = u.norm_inf();
          std::cout << "input:    [-4, -2]\nexpected: 6, 4.47214, 4\nresult:   " << n1 << ", " << n2 << ", " << ni << "\n\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
