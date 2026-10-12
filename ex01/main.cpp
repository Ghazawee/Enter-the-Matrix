#include "../include/Vector.hpp"

// ex01: linear_combination. Each test prints the input, the expected result, then the result.
// linear_combination takes a list of vectors (std::vector<Vector<float>>) and a list of weights (std::vector<float>).

int main() {
    try {
        std::cout << "========== Subject examples ==========\n";
        {
            Vector<float> e1 = {1, 0, 0};
            Vector<float> e2 = {0, 1, 0};
            Vector<float> e3 = {0, 0, 1};
            std::vector<Vector<float>> list = {e1, e2, e3};
            std::vector<float> weights = {10, -2, 0.5};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [1, 0, 0], [0, 1, 0], [0, 0, 1] with weights [10, -2, 0.5]\nexpected: [10, -2, 0.5]\nresult:\n" << r << "\n";
        }
        {
            Vector<float> v1 = {1, 2, 3};
            Vector<float> v2 = {0, 10, -100};
            std::vector<Vector<float>> list = {v1, v2};
            std::vector<float> weights = {10, -2};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [1, 2, 3], [0, 10, -100] with weights [10, -2]\nexpected: [10, 0, 230]\nresult:\n" << r << "\n";
            std::cout << "input:    v1 after being used\nexpected: [1, 2, 3] (unchanged)\nresult:\n" << v1 << "\n";
        }

        std::cout << "========== More inputs ==========\n";
        {
            std::vector<Vector<float>> list = {{-42, 42}};
            std::vector<float> weights = {-1};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [-42, 42] with weights [-1]\nexpected: [42, -42]\nresult:\n" << r << "\n";
        }
        {
            std::vector<Vector<float>> list = {{-42}, {-42}, {-42}};
            std::vector<float> weights = {-1, 1, 0};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [-42], [-42], [-42] with weights [-1, 1, 0]\nexpected: [0]\nresult:\n" << r << "\n";
        }
        {
            std::vector<Vector<float>> list = {{-42, 42}, {1, 3}, {10, 20}};
            std::vector<float> weights = {1, -10, -1};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [-42, 42], [1, 3], [10, 20] with weights [1, -10, -1]\nexpected: [-62, -8]\nresult:\n" << r << "\n";
        }
        {
            std::vector<Vector<float>> list = {{-42, 100, -69.5}, {1, 3, 5}};
            std::vector<float> weights = {1, -10};
            Vector<float> r = linear_combination(list, weights);
            std::cout << "input:    [-42, 100, -69.5], [1, 3, 5] with weights [1, -10]\nexpected: [-52, 70, -119.5]\nresult:\n" << r << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << "\n";
    }
    return 0;
}
