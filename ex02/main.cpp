#include "../include/lerp.hpp"

// ex02: lerp. Each test prints the input, the expected result, then the result.
// The same lerp works on plain floats, Vectors and Matrices (one test each kind below).

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        { float r = lerp(0.f, 1.f, 0.f);
          std::cout << "input:    lerp(0, 1, 0)\nexpected: 0\nresult:   " << r << "\n\n"; }
        { float r = lerp(0.f, 1.f, 1.f);
          std::cout << "input:    lerp(0, 1, 1)\nexpected: 1\nresult:   " << r << "\n\n"; }
        { float r = lerp(0.f, 1.f, 0.5f);
          std::cout << "input:    lerp(0, 1, 0.5)\nexpected: 0.5\nresult:   " << r << "\n\n"; }
        { float r = lerp(21.f, 42.f, 0.3f);
          std::cout << "input:    lerp(21, 42, 0.3)\nexpected: 27.3\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {2, 1}; Vector<float> v = {4, 2}; Vector<float> r = lerp(u, v, 0.3f);
          std::cout << "input:    lerp([2, 1], [4, 2], 0.3)   (vectors)\nexpected: [2.6, 1.3]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{2, 1}, {3, 4}}; Matrix<float> b = {{20, 10}, {30, 40}}; Matrix<float> r = lerp(a, b, 0.5f);
          std::cout << "input:    lerp([[2, 1], [3, 4]], [[20, 10], [30, 40]], 0.5)   (matrices)\nexpected: [[11, 5.5], [16.5, 22]]\nresult:\n" << r << "\n"; }

        std::cout << "========== More inputs ==========\n";
        { float r = lerp(0.f, 42.f, 0.5f);
          std::cout << "input:    lerp(0, 42, 0.5)\nexpected: 21\nresult:   " << r << "\n\n"; }
        { float r = lerp(-42.f, 42.f, 0.5f);
          std::cout << "input:    lerp(-42, 42, 0.5)\nexpected: 0\nresult:   " << r << "\n\n"; }
        { Vector<float> u = {-42, 42}; Vector<float> v = {42, -42}; Vector<float> r = lerp(u, v, 0.5f);
          std::cout << "input:    lerp([-42, 42], [42, -42], 0.5)\nexpected: [0, 0]\nresult:\n" << r << "\n"; }
        { Matrix<float> a = {{0, 0}, {0, 0}}; Matrix<float> b = {{10, -10}, {4, 100}}; Matrix<float> r = lerp(a, b, 0.25f);
          std::cout << "input:    lerp([[0, 0], [0, 0]], [[10, -10], [4, 100]], 0.25)   (matrices)\nexpected: [[2.5, -2.5], [1, 25]]\nresult:\n" << r << "\n"; }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
