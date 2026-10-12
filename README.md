# Enter the Matrix

42 project "Enter the Matrix": an introduction to linear algebra, written in C++11.
Mandatory part, ex00 to ex13.

| ex | What |
|---|---|
| 00 | add, subtract, scale (vectors and matrices) |
| 01 | linear combination |
| 02 | linear interpolation (lerp) |
| 03 | dot product |
| 04 | norms: Manhattan, Euclidean, supremum |
| 05 | cosine of the angle between two vectors |
| 06 | cross product |
| 07 | matrix × vector, matrix × matrix |
| 08 | trace |
| 09 | transpose |
| 10 | reduced row-echelon form |
| 11 | determinant |
| 12 | inverse |
| 13 | rank |

## Build and run

```sh
make            # builds one test program per exercise: ex00/test ... ex13/test
./ex00/test     # each line prints the input, the expected result, and the result
make re         # rebuild from scratch (also: clean, fclean)
```

## Layout

- `include/Vector.hpp`, `include/Matrix.hpp`, `include/lerp.hpp`: the library (header-only templates, `Vector<K>` and `Matrix<K>`).
- `exNN/main.cpp`: the tests for exercise NN (the subject's examples and more inputs).

Matrices are written row by row: `Matrix<float> a = {{1, 2}, {3, 4}};` has rows `[1, 2]` and `[3, 4]`.
Invalid input (different sizes, not square, no inverse, out-of-range index, inf or nan) throws an exception instead of crashing.
