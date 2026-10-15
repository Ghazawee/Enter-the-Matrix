# Enter the Matrix

![language](https://img.shields.io/badge/language-C%2B%2B11-blue)
![part](https://img.shields.io/badge/part-mandatory%20(ex00--ex13)-green)
![school](https://img.shields.io/badge/42-Abu%20Dhabi-black)

**matrix** (MAT 211, "Enter the Matrix: an introduction to linear algebra") is a 42 Abu Dhabi project in which you build the core of a small linear algebra library from scratch: vectors, matrices, and the classic operations on them (linear combination, interpolation, dot product, norms, cosine, cross product, matrix multiplication, trace, transpose, row echelon form, determinant, inverse, rank). It is written in **C++11** as two header-only templates, `Vector<K>` and `Matrix<K>`, with no math library: only the few functions the subject allows (`fma`, `pow`, `max`). Every exercise has its own test program, including the subject's examples and extra edge cases. This repository covers the **mandatory part only (ex00 to ex13)**.

Author: Ghazawee.

## Table of contents

1. [Build and run](#build-and-run)
2. [Design overview](#design-overview)
3. [Exercises](#exercises): [ex00](#ex00---add-subtract-and-scale), [ex01](#ex01---linear-combination), [ex02](#ex02---linear-interpolation), [ex03](#ex03---dot-product), [ex04](#ex04---norm), [ex05](#ex05---cosine), [ex06](#ex06---cross-product), [ex07](#ex07---linear-map-and-matrix-multiplication), [ex08](#ex08---trace), [ex09](#ex09---transpose), [ex10](#ex10---row-echelon-form), [ex11](#ex11---determinant), [ex12](#ex12---inverse), [ex13](#ex13---rank)
4. [Repository layout](#repository-layout)
5. [Summary table](#summary-table)

## Build and run

Linux or WSL, with `c++` (g++ or clang++).

```sh
make              # builds ex00/test ... ex13/test
./ex00/test       # run one exercise's test program
./ex12/test
make clean        # remove the .o files
make fclean       # remove the .o files and the test binaries
make re           # fclean, then all
```

Compiler flags (from the `Makefile`): `c++ -Wall -Wextra -Werror -std=c++11 -O2 -I include`. Each `exNN/main.cpp` includes the headers from `include/` and prints its results next to the expected values.

## Design overview

| Topic | What the code does |
|---|---|
| Templates | `Vector<K>` wraps a `std::vector<K>`; `Matrix<K>` wraps `rows`, `cols` and one flat `std::vector<K>`. Both are header-only (templates must live in headers). The mandatory part only needs `K = float`. |
| Storage | Matrices are **row-major**: element `(i, j)` is at `_data[i * _cols + j]`. `Matrix<float> m = {{1, 2}, {3, 4}}` means the rows `[1 2]` and `[3 4]`. |
| Mutate or return | The ex00 operations (`add`, `sub`, `scl`) **mutate** the object, as the subject prototypes show (`&mut self`). The `+`, `-`, `*` operators are thin pure wrappers around them. Every other exercise returns a new value and leaves its inputs untouched. |
| Errors | A size or shape mismatch throws `std::invalid_argument`; out-of-range access throws `std::out_of_range` (`operator[]` uses `.at()`, `operator()` checks the indices); a result that is `inf` or `NaN` throws `std::overflow_error` (`check_finite`). A singular matrix in `inverse` throws `std::invalid_argument`. |
| Lambdas | One private `apply` helper per class takes a lambda `[](K a, K b){ return a + b; }` and runs it element by element, so `add` and `sub` share all their checking code. |
| `fma` | `std::fma(a, b, c)` computes `a * b + c` with a single rounding. It is used for every multiply-accumulate loop: linear combination, lerp on scalars, dot product, `norm`, `mul_vec`, `mul_mat`. |
| Overflow safety | `norm`, `angle_cos`, `row_echelon`, `inverse` first divide by the largest absolute value (so the biggest number becomes 1), compute, then scale back where needed. This avoids `1e20 * 1e20` overflowing and `1e-30 * 1e-30` rounding to 0. |
| Zero tests and pivoting | Gaussian elimination (ex10 to ex13) uses **partial pivoting** (largest absolute value in the column becomes the pivot) and a tolerance of `1e-6` relative to the biggest number. |
| Helpers | `ft_abs` (own absolute value, `abs` is not allowed), `check_finite`, `Matrix::is_square`, `Matrix::biggest_abs`, and `operator<<` printing like the subject (`[x]` per line for vectors, `[a, b]` per row for matrices; `-0` is printed as `0`). |
| Complexity | Every exercise has a short proof of its time and space bound, derived by counting the loops of the code shown (see the "Complexity (proof)" part of each exercise). All bounds meet the limits the subject sets. |

The `fma` hardware instruction and the tolerance are the only "numerical" choices; everything else is plain loops.

## Exercises

Complexity notation: $n$, $m$ and $p$ are the sizes defined by each exercise (number of coordinates, or the dimensions of a matrix). "Limit" is the maximum the subject allows. In the proofs, a "constant-time operation" is one that takes the same time whatever the input size (one addition, one comparison, one `fma`, one assignment).

### ex00 - Add, Subtract and Scale

**Goal.** Add and subtract two vectors (or two matrices) of the same size, and multiply a vector or matrix by a scalar. These are the three operations that make vectors and matrices a vector space: everything else is built on them.

**What it does.**

| Call | Input | Output |
|---|---|---|
| `u.add(v)` | `u = [2, 3]`, `v = [5, 7]` | `u = [7, 10]` |
| `u.sub(v)` | `u = [2, 3]`, `v = [5, 7]` | `u = [-3, -4]` |
| `u.scl(2)` | `u = [2, 3]` | `u = [4, 6]` |
| `a.add(b)` | `a = [[1, 2], [3, 4]]`, `b = [[7, 4], [-2, 2]]` | `a = [[8, 6], [1, 6]]` |
| `a.scl(2)` | `a = [[1, 2], [3, 4]]` | `a = [[2, 4], [6, 8]]` |

**Formula.**

$$u + v = \begin{bmatrix} u_1 + v_1 \\ \vdots \\ u_n + v_n \end{bmatrix}, \qquad a \cdot u = \begin{bmatrix} a\,u_1 \\ \vdots \\ a\,u_n \end{bmatrix}$$

Reading: add (or subtract) the two lists position by position; scaling multiplies every entry by the same number `a`. Matrices work identically, entry by entry.

**Code** (`include/Vector.hpp`, lines 33-42 and 56-58):

```cpp
    template <typename F>
    void apply(const Vector<K>& v, F op, const char* msg){
        if (this->size() != v.size())
            throw std::invalid_argument(msg);
        for(size_t i = 0; i < this->size(); i++){
            K value = op(_data[i], v[i]);
            check_finite(value);            // check before writing: an overflow never lands in the vector
            _data[i] = value;
        }
    }
```

```cpp
    void add(const Vector<K>& v){
        apply(v, [](K a, K b){return a + b;}, "add: size mismatch");
    }
```

#### Complexity (proof)

Let $n$ be the number of coordinates (for a matrix, $n = \text{rows} \cdot \text{cols}$). Time:

- The size check runs once: 1 constant-time operation.
- The loop over `i` runs exactly $n$ times. Inside it: one `op` (an addition or subtraction), one `check_finite`, one store: 3 constant-time operations.

$$T(n) = 1 + \sum_{i=1}^{n} 3 = 3n + 1 \in O(n)$$

For a matrix the same body sits in two nested loops, $\text{rows}$ times $\text{cols}$ iterations, which is again $3n + 1$ operations. The constant 3 and the additive 1 are dropped because they do not grow with $n$.

Space: the result is written back into the object, and the only new variables are `i` and `value`, which do not depend on $n$: $S(n) \in O(1)$ extra.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex01 - Linear combination

**Goal.** Given vectors $u_1, \dots, u_k$ and coefficients $c_1, \dots, c_k$, compute $c_1 u_1 + \dots + c_k u_k$. Linear combinations are how every vector in a space is described from a basis.

**What it does.** With `u1 = [1, 2, 3]`, `u2 = [0, 10, -100]` and coefficients `[10, -2]`:
`10 * [1, 2, 3] = [10, 20, 30]`, `-2 * [0, 10, -100] = [0, -20, 200]`, sum `[10, 0, 230]`.

**Formula.**

$$\sum_{i=1}^{k} c_i\,u_i = c_1 \begin{bmatrix} 1 \\ 2 \\ 3 \end{bmatrix} + c_2 \begin{bmatrix} 0 \\ 10 \\ -100 \end{bmatrix} \quad\text{with } c = (10, -2) \text{ gives } \begin{bmatrix} 10 \\ 0 \\ 230 \end{bmatrix}$$

Reading: scale each vector by its coefficient, then add them all together.

**Code** (`include/Vector.hpp`, lines 132-148):

```cpp
template <typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs){
    if (u.size() != coefs.size())
        throw std::invalid_argument("linear_combination: wrong number of coefficients");
    if (u.empty())
        throw std::invalid_argument("linear_combination: empty list");
    Vector<K> result(u[0].size());
    for (size_t i = 0; i < u.size(); i++){
        if (u[i].size() != result.size())
            throw std::invalid_argument("linear_combination: vectors size mismatch");
        for (size_t j = 0; j < u[i].size(); j++){
            result[j] = std::fma(coefs[i], u[i][j], result[j]); //formula is a * b + c, a=coefs[i], b=u[i][j], c=result[j], can be written as result[j] += u[i][j] * coefs[i]; but fma is more precise and faster on some platforms
            check_finite(result[j]);
        }
    }
    return result;
}
```

#### Complexity (proof)

Let $k$ be the number of vectors and $d$ the size of each one, so the total number of coordinates is $n = k \cdot d$. Time:

- `Vector<K> result(u[0].size())` fills $d$ zeros.
- The outer loop over `i` runs $k$ times; each time it does one size check (1 operation).
- The inner loop over `j` runs $d$ times per outer iteration. Inside: one `fma` and one `check_finite`: 2 constant-time operations.

$$T(n) = \underbrace{d}_{\text{zero-fill}} + \sum_{i=1}^{k} \Big( \underbrace{1}_{\text{size check}} + \sum_{j=1}^{d} \underbrace{2}_{\text{fma, check}} \Big) = d + k + 2kd$$

Since $k \ge 1$ and $d \ge 1$, we have $d + k \le 2kd$, so $T(n) \le 4kd = 4n \in O(n)$. Constants are dropped because they do not grow with $n$.

Space: only `result`, with $d$ numbers, and $d \le n$, so $S(n) = d \in O(n)$.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex02 - Linear interpolation

**Goal.** Compute the point a fraction $t \in [0, 1]$ of the way from $u$ to $v$ (`lerp`). It works on floats, vectors and matrices alike, and is the basis of animation, blending and gradients.

**What it does.**

| Call | Output |
|---|---|
| `lerp(2.f, 6.f, 0.25f)` | `3` (a quarter of the way from 2 to 6) |
| `lerp([2, 1], [4, 2], 0.3)` | `[2.6, 1.3]` (0.7 * 2 + 0.3 * 4 = 2.6, 0.7 * 1 + 0.3 * 2 = 1.3) |

**Formula.**

$$\text{lerp}(u, v, t) = (1 - t)\,u + t\,v$$

Reading: keep `(1 - t)` of `u` and take `t` of `v`; at `t = 0` you get `u`, at `t = 1` you get `v`, at `t = 0.5` the exact middle. This form never overflows where $u + t(v - u)$ would (the difference `FLT_MAX - (-FLT_MAX)` is infinite).

**Code** (`include/lerp.hpp`, lines 12-22):

```cpp
template <typename V>
V lerp(const V& u, const V& v, float t){
    return u * (1 - t) + v * t;
}

template<>
inline float lerp(const float& u, const float& v, float t){
    float result = std::fma(t, v, (1 - t) * u);   // t * v + (1 - t) * u
    check_finite(result);
    return result;
}
```

The generic version reuses the ex00 operators (so it works for any `Vector` or `Matrix`); floats get a specialisation that uses `fma`.

#### Complexity (proof)

Let $n$ be the number of coordinates of `u` (and `v`). The generic version is `u * (1 - t) + v * t`, which calls three ex00 operators. Each takes its first argument by value, so each starts with a copy of $n$ numbers:

- `u * (1 - t)`: copy $n$, then `scl` loops $n$ times: $2n$.
- `v * t`: copy $n$, then `scl` loops $n$ times: $2n$.
- `+`: copy $n$ (at most; the compiler may move the temporary instead), then `add` loops $n$ times: at most $2n$.

$$T(n) \le \underbrace{2n}_{u \cdot (1-t)} + \underbrace{2n}_{v \cdot t} + \underbrace{2n}_{\text{sum}} = 6n \in O(n)$$

The constant 6 is dropped. For a `float`, $n = 1$ and the specialisation does one `fma` and one check, so $T \in O(1)$.

Space: the two temporaries and the result each hold $n$ numbers, so $S(n) \le 3n \in O(n)$.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex03 - Dot product

**Goal.** Multiply two vectors of the same size coordinate by coordinate and add the products. The dot product measures how much two vectors point the same way, and is the building block for norms, angles and matrix products.

**What it does.** `[1, 2, 3] . [4, 5, 6] = 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32`.

**Formula.**

$$u \cdot v = \sum_{i=1}^{n} u_i\,v_i = \begin{bmatrix} 1 \\ 2 \\ 3 \end{bmatrix} \cdot \begin{bmatrix} 4 \\ 5 \\ 6 \end{bmatrix} = 32$$

Reading: pair up the entries, multiply each pair, add everything.

**Code** (`include/Vector.hpp`, lines 73-82):

```cpp
    K dot(const Vector<K>& v)const{
        if (this->size() != v.size())
            throw std::invalid_argument("dot: size mismatch");
        K result = K();
        for(size_t i = 0; i < this->size(); i++){
            result = std::fma(_data[i], v[i], result); //formula is a * b + c, a=_data[i], b=v[i], c=result, can be written as result += _data[i] * v[i];
        }
        check_finite(result);   // once a sum becomes inf or nan it stays that way, so checking the end is enough
        return result;
    }
```

#### Complexity (proof)

Let $n$ be the number of coordinates. Time:

- The size check and `K result = K()` run once: 2 constant-time operations.
- The loop over `i` runs exactly $n$ times, with one `fma` inside: 1 operation.
- `check_finite(result)` runs once after the loop: 1 operation.

$$T(n) = 2 + \sum_{i=1}^{n} 1 + 1 = n + 3 \in O(n)$$

The $+3$ is dropped because it does not grow with $n$.

Space: only `result` and `i`: $S(n) \in O(1)$.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex04 - Norm

**Goal.** Measure the "length" of a vector in three ways: the 1-norm (sum of absolute values), the 2-norm (Euclidean length) and the infinity norm (largest absolute value). Norms define distance and size in a vector space.

**What it does.** For `v = [-3, 4]`: `norm_1 = |-3| + |4| = 7`, `norm = sqrt(9 + 16) = 5`, `norm_inf = max(3, 4) = 4`.

**Formula.**

$$\|v\|_1 = \sum_{i=1}^{n} |v_i|, \qquad \|v\|_2 = \sqrt{\sum_{i=1}^{n} v_i^2}, \qquad \|v\|_\infty = \max_i |v_i|$$

Reading: add the sizes, take the root of the sum of squares, or just keep the biggest size. The 2-norm is computed as $\|v\|_\infty \cdot \sqrt{\sum (v_i / \|v\|_\infty)^2}$, which is the same number but cannot overflow or underflow in the squares. The square root is `pow(x, 0.5)`, the only root allowed.

**Code** (`include/Vector.hpp`, lines 97-118):

```cpp
    float norm() const{
        float biggest = norm_inf();
        if (biggest == 0.f)
            return 0.f;
        float total = 0.f;
        for(size_t i = 0; i < this->size(); i++){
            float x = _data[i] / biggest;   // now between -1 and 1
            total = std::fma(x, x, total);
        }
        float result = biggest * std::pow(total, 0.5f);
        check_finite(result);
        return result;
    }

    float norm_inf() const{
        float maximum = 0.f;
        for(size_t i = 0; i < this->size(); i++){
            check_finite(_data[i]);         // std::max would silently skip a nan
            maximum = std::max(maximum, ft_abs(_data[i]));
        }
        return maximum;
    }
```

`norm_1` is the same single loop with `total += ft_abs(_data[i])` (`include/Vector.hpp`, lines 86-93).

#### Complexity (proof)

Let $n$ be the number of coordinates. Each function is a sum over the loops it runs:

- `norm_1`: one loop of $n$ iterations, each doing an absolute value and an addition (2 operations), plus one final check: $T_{1}(n) = 2n + 1 \in O(n)$.
- `norm_inf`: one loop of $n$ iterations, each doing `check_finite`, `ft_abs` and `std::max` (3 operations): $T_{\infty}(n) = 3n \in O(n)$.
- `norm`: it first calls `norm_inf`, then runs its own loop of $n$ iterations, each doing one division and one `fma` (2 operations), then one `pow` and one check (constant).

$$T_{2}(n) = \underbrace{3n}_{\text{norm\_inf}} + \underbrace{2n}_{\text{own loop}} + \underbrace{3}_{\text{pow}\text{, checks}} = 5n + 3 \in O(n)$$

Making two passes instead of one only changes the constant ($2n$ is still linear), so the lower terms and constants are dropped.

Space: a few floats (`total`, `biggest`, `x`, `maximum`) and no copy of the vector: $S(n) \in O(1)$.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex05 - Cosine

**Goal.** Compute the cosine of the angle between two vectors. It is 1 for the same direction, 0 for perpendicular vectors and -1 for opposite directions: a standard similarity measure.

**What it does.**

| `u` | `v` | Output |
|---|---|---|
| `[1, 0]` | `[1, 1]` | `0.707107` (`1 / sqrt(2)`) |
| `[1, 2, 3]` | `[4, 5, 6]` | `0.974632` (`32 / sqrt(14 * 77)`) |

**Formula.**

$$\cos\theta = \frac{u \cdot v}{\|u\|\,\|v\|}$$

Reading: the dot product, divided by the product of the two lengths. Shrinking a vector does not change its direction, so the code first divides each vector by its own largest entry (no overflow), then applies the formula. The result is clamped into $[-1, 1]$ against rounding. Zero vectors have no angle and throw.

**Code** (`include/Vector.hpp`, lines 154-174):

```cpp
template <typename K>
float angle_cos(const Vector<K>& u, const Vector<K>& v){
    if (u.size() != v.size())
        throw std::invalid_argument("angle_cos: size mismatch");
    float u_big = u.norm_inf();     // also throws if u contains inf or nan
    float v_big = v.norm_inf();
    if (u_big == 0.f || v_big == 0.f)
        throw std::invalid_argument("angle_cos: undefined for zero vectors");
    Vector<K> a = u;
    Vector<K> b = v;
    for (size_t i = 0; i < a.size(); i++){
        a[i] = a[i] / u_big;
        b[i] = b[i] / v_big;
    }
    float result = a.dot(b) / (a.norm() * b.norm());
    if (result < -1.f)
        return -1.f;
    if (result > 1.f)
        return 1.f;
    return result;
}
```

#### Complexity (proof)

Let $n$ be the common number of coordinates. Count one "pass" as a loop of $n$ constant-time steps:

- `u.norm_inf()` and `v.norm_inf()`: 1 pass each.
- `Vector<K> a = u;` and `Vector<K> b = v;`: 1 copy pass each.
- The shrink loop over `i` runs $n$ times (two divisions per iteration): 1 pass.
- `a.dot(b)`: 1 pass (ex03).
- `a.norm()` and `b.norm()`: 2 passes each (`norm_inf`, then its own loop; ex04).

$$T(n) = \underbrace{2n}_{\text{norm\_inf}\times 2} + \underbrace{2n}_{\text{copies}} + \underbrace{n}_{\text{shrink}} + \underbrace{n}_{\text{dot}} + \underbrace{4n}_{\text{norm}\times 2} + O(1) = 10n + O(1) \in O(n)$$

A fixed number of passes (10) is a constant, so it is dropped.

Space: the copies `a` and `b` hold $n$ numbers each, so $S(n) = 2n \in O(n)$.

Subject limit: time $O(n)$, space $O(n)$. Both are met.

### ex06 - Cross product

**Goal.** For two 3D vectors, compute a third vector perpendicular to both, whose length is the area of the parallelogram they span. Used for normals, torque and orientation tests.

**What it does.** `[1, 2, 3] x [4, 5, 6]`: `2*6 - 3*5 = -3`, `3*4 - 1*6 = 6`, `1*5 - 2*4 = -3`, so the result is `[-3, 6, -3]`.

**Formula.**

$$u \times v = \begin{bmatrix} u_2 v_3 - u_3 v_2 \\ u_3 v_1 - u_1 v_3 \\ u_1 v_2 - u_2 v_1 \end{bmatrix}, \qquad \begin{bmatrix} 1 \\ 2 \\ 3 \end{bmatrix} \times \begin{bmatrix} 4 \\ 5 \\ 6 \end{bmatrix} = \begin{bmatrix} -3 \\ 6 \\ -3 \end{bmatrix}$$

Reading: each component is a 2-by-2 "cross" of the other two coordinates. Swapping `u` and `v` flips the sign.

**Code** (`include/Vector.hpp`, lines 177-189):

```cpp
template <typename K>
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v){
    if (u.size() != 3 || v.size() != 3)
        throw std::invalid_argument("cross_product: not a 3D vectors");
    Vector<K> result(3);
    result[0] = u[1] * v[2] - u[2] * v[1];
    result[1] = u[2] * v[0] - u[0] * v[2];
    result[2] = u[0] * v[1] - u[1] * v[0];
    check_finite(result[0]);
    check_finite(result[1]);
    check_finite(result[2]);
    return result;
}
```

#### Complexity (proof)

There is no loop. The function first checks that both sizes are exactly 3; any other size throws before any computation, so the input size is fixed at 3 and cannot grow. Then:

- 3 components, each with 2 multiplications and 1 subtraction: $3 \cdot 3 = 9$ operations (6 multiplications, 3 subtractions).
- 3 calls to `check_finite`: 3 operations.
- The result vector has 3 numbers.

$$T = 9 + 3 = 12 \in O(1), \qquad S = 3 \in O(1)$$

The count 12 is the same for every valid input, so the time is constant. The space is the 3-number result, also constant.

Subject limit: none (N/A). A vector that is not 3D throws (the subject calls this undefined).

### ex07 - Linear map and matrix multiplication

**Goal.** Apply a matrix to a vector (`mul_vec`, a linear map) and multiply two matrices (`mul_mat`, composing two linear maps). Matrix-vector products are how rotations, scalings and projections are carried out; matrix products chain them.

**What it does.**

| Call | Input | Output |
|---|---|---|
| `mul_vec` | `[[2, -2], [-2, 2]]` and `[4, 2]` | `[4, -4]` |
| `mul_mat` | `[[3, -5], [6, 8]]` and `[[2, 1], [4, 2]]` | `[[-14, -7], [44, 22]]` |

Check of the second: `3*2 + (-5)*4 = -14`, `3*1 + (-5)*2 = -7`, `6*2 + 8*4 = 44`, `6*1 + 8*2 = 22`.

**Formula.**

$$(Au)_i = \sum_{j=1}^{n} A_{ij}\,u_j, \qquad (AB)_{ij} = \sum_{k=1}^{n} A_{ik}\,B_{kj}$$

$$\begin{bmatrix} 3 & -5 \\ 6 & 8 \end{bmatrix} \begin{bmatrix} 2 & 1 \\ 4 & 2 \end{bmatrix} = \begin{bmatrix} -14 & -7 \\ 44 & 22 \end{bmatrix}$$

Reading: entry `(i, j)` of the product is the dot product of row `i` of the left matrix with column `j` of the right one. For $A \in \mathbb{R}^{m \times n}$ and $B \in \mathbb{R}^{n \times p}$ the result is $m \times p$; the inner sizes $n$ must match.

**Code** (`include/Matrix.hpp`, lines 98-109 and 113-126):

```cpp
    Vector<K> mul_vec(const Vector<K>& u) const {
        if (this->cols() != u.size())
            throw std::invalid_argument("mul_vec: size mismatch");
        Vector<K> result(this->rows());
        for (size_t i = 0; i < this->rows(); i++){
            for(size_t j = 0; j < this->cols(); j++){
                result[i] = std::fma((*this)(i, j), u[j], result[i]); //formula is a * b + c, a=(*this)(i, j), b=u[j], c=result[i], can be written as result[i] += (*this)(i, j) * u[j];
                check_finite(result[i]);
            }
        }
        return result;
    }
```

```cpp
    Matrix<K> mul_mat(const Matrix<K>& b) const {
        if (this->cols() != b.rows())
            throw std::invalid_argument("mul_mat: size mismatch"); // rule is: (m x n) * (n x p) = (m x p), n must match
        Matrix<K> result(this->rows(), b.cols());
        for (size_t i = 0; i < this->rows(); i++){
            for (size_t j = 0; j < b.cols(); j++){
                for (size_t k = 0; k < this->cols(); k++){
                    result(i, j) = std::fma((*this)(i, k), b(k, j), result(i, j));
                    check_finite(result(i, j));
                }
            }
        }
        return result;
    }
```

#### Complexity (proof)

Here $A$ is $m \times n$ (`m` rows, `n` columns), `u` has $n$ numbers and $B$ is $n \times p$.

`mul_vec`:

- The loop over `i` runs $m$ times; the loop over `j` runs $n$ times per `i`. Inside: one `fma` and one `check_finite` (2 operations).

$$T_{\text{vec}}(m, n) = \sum_{i=1}^{m} \sum_{j=1}^{n} 2 = 2mn \in O(nm)$$

- Space: the result vector has $m$ numbers: $S = m \in O(m)$.
- Subject limit: time $O(nm)$, space $O(nm)$. Both are met.

`mul_mat`:

- The loop over `i` runs $m$ times, the loop over `j` runs $p$ times per `i`, and the loop over `k` runs $n$ times per `j`. Inside: one `fma` and one `check_finite` (2 operations). The result is first zero-filled with $mp$ numbers.

$$T_{\text{mat}}(m, n, p) = \underbrace{mp}_{\text{zero-fill}} + \sum_{i=1}^{m} \sum_{j=1}^{p} \sum_{k=1}^{n} 2 = mp + 2mnp \in O(nmp)$$

The zero-fill $mp$ is at most $mnp$, so it is absorbed, and the constant 2 is dropped.

- Space: the result matrix has $m \cdot p$ numbers: $S = mp \in O(mp)$.
- Subject limit: time $O(nmp)$, space $O(nm + mp + np)$. Both are met ($mp$ is one of the three terms).

### ex08 - Trace

**Goal.** Sum the diagonal of a square matrix. The trace is unchanged by a change of basis and equals the sum of the eigenvalues.

**What it does.** `[[2, -5, 0], [4, 3, 7], [-2, 3, 4]]` has diagonal `2, 3, 4`, so the trace is `9`.

**Formula.**

$$\mathrm{tr}(A) = \sum_{i=1}^{n} A_{ii} = 2 + 3 + 4 = 9 \quad\text{for}\quad A = \begin{bmatrix} 2 & -5 & 0 \\ 4 & 3 & 7 \\ -2 & 3 & 4 \end{bmatrix}$$

Reading: add the entries whose row number equals their column number. A non-square matrix throws.

**Code** (`include/Matrix.hpp`, lines 129-138):

```cpp
    K trace() const {
        if (!this->is_square())
            throw std::invalid_argument("trace: not a square matrix");
        K result = K();
        for (size_t i = 0; i < this->rows(); i++){
            result += (*this)(i, i);
            check_finite(result);
        }
        return result;
    }
```

#### Complexity (proof)

Let $n$ be the side of the square matrix. Time:

- The square check and `K result = K()`: 2 constant-time operations.
- The loop over `i` runs exactly $n$ times. Inside: one addition and one `check_finite` (2 operations). Only the diagonal is read; the other $n^{2} - n$ entries are never touched.

$$T(n) = 2 + \sum_{i=1}^{n} 2 = 2n + 2 \in O(n)$$

Space: only `result` and `i`: $S(n) \in O(1)$.

Subject limit: time $O(n)$, space N/A. The time bound is met.

### ex09 - Transpose

**Goal.** Mirror a matrix across its diagonal, so rows become columns. Transposing turns an $m \times n$ matrix into an $n \times m$ one and is used constantly in formulas ($A^{T} A$, dot products as matrix products).

**What it does.** `[[1, 2, 3], [4, 5, 6]]` ($2 \times 3$) becomes `[[1, 4], [2, 5], [3, 6]]` ($3 \times 2$).

**Formula.**

$$(A^{T})_{ji} = A_{ij}, \qquad \begin{bmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \end{bmatrix}^{T} = \begin{bmatrix} 1 & 4 \\ 2 & 5 \\ 3 & 6 \end{bmatrix}$$

Reading: the entry in row `i`, column `j` moves to row `j`, column `i`.

**Code** (`include/Matrix.hpp`, lines 141-150):

```cpp
    Matrix<K> transpose() const{
        Matrix<K> result(this->cols(), this->rows());
        for (size_t i = 0; i < this->rows(); i++){
            for (size_t j = 0; j < this->cols(); j++){
                check_finite((*this)(i, j));
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }
```

#### Complexity (proof)

Let the input be $m \times n$ (`m` rows, `n` columns). Time:

- The result `Matrix<K> result(cols, rows)` is zero-filled: $mn$ numbers.
- The loop over `i` runs $m$ times; the loop over `j` runs $n$ times per `i`. Inside: one `check_finite` and one assignment (2 operations).

$$T(m, n) = \underbrace{mn}_{\text{zero-fill}} + \sum_{i=1}^{m} \sum_{j=1}^{n} 2 = 3mn \in O(nm)$$

The constant 3 is dropped.

Space: the new matrix has $n \cdot m$ numbers: $S = nm \in O(nm)$.

Subject limit: time $O(nm)$, space $O(nm)$. Both are met.

### ex10 - Row echelon form

**Goal.** Reduce a matrix with row operations (swap two rows, scale a row, add a multiple of a row to another) until each pivot is 1 and is the only non-zero number in its column. The subject's expected outputs are the **reduced** form (Gauss-Jordan). This is the engine behind solving linear systems, the inverse and the rank.

**What it does.**

| Input | Output |
|---|---|
| `[[1, 2], [3, 4]]` | `[[1, 0], [0, 1]]` |
| `[[1, 2, 3], [4, 5, 6], [7, 8, 9]]` | `[[1, 0, -1], [0, 1, 2], [0, 0, 0]]` |

Steps for the second: the largest pivot candidate in column 1 is 7 (partial pivoting), rows are swapped and normalised; eliminating column 1 and then column 2 leaves the third row all zeros, because `row 3 = 2 * row 2 - row 1`.

**Formula.** Each step is a multiplication by an elementary matrix, for example swapping rows 1 and 2:

$$\begin{bmatrix} 0 & 1 \\ 1 & 0 \end{bmatrix} \begin{bmatrix} a & b \\ c & d \end{bmatrix} = \begin{bmatrix} c & d \\ a & b \end{bmatrix}, \qquad \text{result: } R = E_s \cdots E_2 E_1 A$$

Reading: row operations never change the solutions of the system, so $A$ and $R$ describe the same equations; the pivot of each row is divided to 1, then it is subtracted from every other row (`row_r = row_r - factor * row_lead`).

**Code** (`include/Matrix.hpp`, lines 158-194):

```cpp
        K biggest = biggest_abs();
        // shrink the copy so its biggest number is 1: then one fixed tol works for huge and tiny matrices
        if (biggest > 0){
            for (size_t i = 0; i < m.rows(); i++){
                for (size_t k = 0; k < m.cols(); k++){
                    m(i, k) = m(i, k) / biggest;
                }
            }
        }
        K tol = 1e-6; // anything smaller than this is considered 0
        for(size_t c = 0; c < m.cols() && lead < m.rows(); c++){
            size_t p = lead;
            for (size_t r = lead + 1; r < m.rows(); r++){
                if (ft_abs(m(r, c)) > ft_abs(m(p, c)))
                    p = r;
            }
            if(ft_abs(m(p, c)) <= tol)
                continue; // column is all zeros, go to next column
            if (p != lead){
                for (size_t k = 0; k < m.cols(); k++){
                    std::swap(m(lead, k), m(p, k));
                }
            }
            K pivot = m(lead, c);
            for (size_t k = 0; k < m.cols(); k++){
                m(lead, k) = m(lead, k) / pivot;
            }
            for (size_t r = 0; r < m.rows(); r++){
                if (r != lead){
                    K factor = m(r, c);
                    for (size_t k = 0; k < m.cols(); k++){
                        m(r, k) = m(r, k) - factor * m(lead, k);
                    }
                }
            }
            lead++;
        }
```

After this loop a cleanup pass sets every number with absolute value at most `tol` to an exact 0 (so no `1e-8` or `-0` is printed) and checks for `inf`/`NaN`.

#### Complexity (proof)

Let $n = \max(\text{rows}, \text{cols})$, so the matrix has at most $n^{2}$ numbers and every count below is an upper bound. Time:

- Before the main loop: the copy `Matrix<K> m = *this`, `biggest_abs()` and the shrink loop each visit every number once: $3n^{2}$.
- The column loop `c` runs at most $n$ times. In one iteration:
  - the pivot search (loop `r`) runs at most $n$ times;
  - the row swap (loop `k` over the columns) runs at most $n$ times;
  - the normalisation of the pivot row (loop `k`) runs $n$ times;
  - the elimination (loop `r` over the rows, with the inner loop `k` over the columns) runs at most $n$ rows $\times$ $n$ numbers $= n \cdot n$ times.
- After the main loop: the cleanup pass visits every number once: $n^{2}$.

Each counted step is a constant number of operations, so with the cleanup:

$$T(n) \le \underbrace{3n^{2}}_{\text{copy, largest value, shrink}} + \sum_{c=1}^{n} \Big( \underbrace{n}_{\text{find pivot}} + \underbrace{n}_{\text{swap}} + \underbrace{n}_{\text{normalise}} + \underbrace{n \cdot n}_{\text{eliminate}} \Big) + \underbrace{n^{2}}_{\text{cleanup}} = n^{3} + 7n^{2} \in O(n^{3})$$

The lower term $7n^{2}$ is dropped because for large $n$ it is tiny next to $n^{3}$.

Space: the working copy `m` holds $n^{2}$ numbers (it is the returned value); everything else (`lead`, `biggest`, `tol`, `p`, `pivot`, `factor`) is a single number. So $S(n) = n^{2} \in O(n^{2})$.

Subject limit: time $O(n^{3})$, space $O(n^{2})$. Both are met.

### ex11 - Determinant

**Goal.** Compute the single number that says how a square matrix scales volume (area in 2D), and whether it flattens space: `det = 0` means the matrix is singular.

**What it does.**

| Input | Output |
|---|---|
| `[[3, -5], [6, 8]]` | `3*8 - (-5)*6 = 54` |
| `[[8, 5, -2], [4, 7, 20], [7, 6, 1]]` | `-174` |
| `[[1, 2], [3, 4]]` | `-2` |

**Formula.**

$$\det\begin{bmatrix} a & b \\ c & d \end{bmatrix} = ad - bc, \qquad \det(A) = (-1)^{s} \prod_{i=1}^{n} p_i$$

Reading: the code reduces `A` to an upper-triangular matrix with row operations (which keep the determinant), counts `s` row swaps (each swap flips the sign), and multiplies the pivots $p_i$ on the diagonal. If a column has no pivot, the result is 0.

**Code** (`include/Matrix.hpp`, lines 215-240):

```cpp
        for(size_t c = 0; c < m.cols() && lead < m.rows(); c++){
            size_t p = lead;
            for (size_t r = lead + 1; r < m.rows(); r++){
                if (ft_abs(m(r, c)) > ft_abs(m(p, c)))
                    p = r;
            }
            if(ft_abs(m(p, c)) <= tol)
                return 0; // no pivot in this column: space is squashed flat, so det = 0
            if (p != lead){
                for (size_t k = 0; k < m.cols(); k++){
                    std::swap(m(lead, k), m(p, k));
                }
                det *= -1; // swapping rows changes the sign of the determinant
            }
            for (size_t r = lead + 1; r < m.rows(); r++){
                K factor = m(r, c) / m(c, c);
                for (size_t k = 0; k < m.cols(); k++){
                    m(r, k) = m(r, k) - factor * m(lead, k);
                }
            }
            det = det * m(c, c);
            lead++;
        }
        check_finite(det);
        return det;
    }
```

Before the loop: `K tol = biggest * 1e-6;`, so "zero" is relative to the biggest number in the matrix. A non-square matrix throws.

#### Complexity (proof)

Let $n$ be the side of the square matrix. This function does its own elimination (it does not call `row_echelon`), and it only clears the rows below the pivot. Time:

- Before the loop: the copy `Matrix<K> m = *this` and `biggest_abs()` each visit every number once: $2n^{2}$.
- The column loop `c` runs at most $n$ times (it returns early if a column has no pivot). In one iteration:
  - the pivot search (loop `r`) runs at most $n$ times;
  - the row swap (loop `k`) runs at most $n$ times;
  - the elimination clears the rows below the pivot: at most $n$ rows, each with one division for `factor` and an inner loop `k` of $n$ steps, so at most $n \cdot n$ steps (the division is absorbed);
  - one multiplication `det = det * m(c, c)`: 1 operation.

$$T(n) \le \underbrace{2n^{2}}_{\text{copy, largest value}} + \sum_{c=1}^{n} \Big( \underbrace{n}_{\text{find pivot}} + \underbrace{n}_{\text{swap}} + \underbrace{n \cdot n}_{\text{eliminate}} + \underbrace{1}_{\text{multiply}} \Big) = n^{3} + 4n^{2} + n \in O(n^{3})$$

The real count is about half of $n^{3}$, because at column $c$ only the $n - c$ rows below the pivot are visited, but a constant factor is dropped anyway, and so are the lower terms $4n^{2} + n$.

Space: the working copy `m` holds $n^{2}$ numbers; `det`, `tol`, `biggest`, `p`, `factor` are single numbers. So $S(n) = n^{2} \in O(n^{2})$.

Subject limit: time $O(n^{3})$, space $O(n^{2})$. Both are met.

### ex12 - Inverse

**Goal.** Find the matrix $A^{-1}$ that undoes $A$, so that $A A^{-1} = I$. It exists only when the determinant is not zero; a singular matrix throws.

**What it does.**

| Input | Output |
|---|---|
| `[[1, 2], [3, 4]]` | `[[-2, 1], [1.5, -0.5]]` |
| `[[2, 0, 0], [0, 2, 0], [0, 0, 2]]` | `[[0.5, 0, 0], [0, 0.5, 0], [0, 0, 0.5]]` |

Check of the first: `det = -2`, and $\frac{1}{-2}\begin{bmatrix} 4 & -2 \\ -3 & 1 \end{bmatrix} = \begin{bmatrix} -2 & 1 \\ 1.5 & -0.5 \end{bmatrix}$.

**Formula.**

$$\left[\, A \mid I \,\right] \xrightarrow{\text{row operations}} \left[\, I \mid A^{-1} \,\right], \qquad \begin{bmatrix} 1 & 2 & 1 & 0 \\ 3 & 4 & 0 & 1 \end{bmatrix} \longrightarrow \begin{bmatrix} 1 & 0 & -2 & 1 \\ 0 & 1 & 1.5 & -0.5 \end{bmatrix}$$

Reading: write `A` next to the identity, run ex10 on the double-width matrix; the row operations that turn `A` into `I` turn `I` into $A^{-1}$. If the left half does not become the identity, `A` is singular.

**Code** (`include/Matrix.hpp`, lines 253-272):

```cpp
        Matrix<K> w(n, 2 * n);
        for (size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                w(i, j) = (*this)(i, j) / biggest; // shrink A so its biggest number is 1, the same size as the identity's 1s
            }
            w(i, n + i) = K(1);
        }
        Matrix<K> r = w.row_echelon();
        for (size_t i = 0; i < n; i++){
            if (r(i, i) != K(1))
                throw std::invalid_argument("inverse: matrix is singular");
        }
        Matrix<K> inv(n, n);
        for(size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                inv(i, j) = r(i, n + j) / biggest; // un-shrink the inverse
                check_finite(inv(i, j));
            }
        }
        return inv;
```

(`biggest` is `biggest_abs()`; an all-zero matrix and a non-square matrix throw earlier, an empty 0x0 matrix returns itself.) The inverse of a scaled matrix $A/s$ is $s\,A^{-1}$, which is why the result is divided by `biggest` at the end.

#### Complexity (proof)

Let $n$ be the side of the square matrix. The function calls `row_echelon` (ex10) on `w`, which has $n$ rows and $2n$ columns. Time:

- `biggest_abs()`: $n^{2}$.
- Building `w`: zero-fill of $2n^{2}$ numbers, the loop over `i` and `j` runs $n \cdot n$ times (one division each), and $n$ ones are written on the identity half: $3n^{2} + n$.
- `w.row_echelon()`: redo the ex10 count with $n$ rows and $2n$ columns. Copy, largest value and shrink visit $2n^{2}$ numbers each: $6n^{2}$. There are at most $n$ pivots (the loop stops once `lead` reaches $n$); each costs $n$ (find pivot) $+ 2n$ (swap) $+ 2n$ (normalise) $+ n \cdot 2n$ (eliminate). The at most $2n$ columns that have no pivot cost only their search of at most $n$ steps: $2n^{2}$. Cleanup: $2n^{2}$.

$$T_{\text{echelon}}(n) \le \underbrace{6n^{2}}_{\text{copy, largest value, shrink}} + \sum_{c=1}^{n} \Big( \underbrace{n}_{\text{find}} + \underbrace{2n}_{\text{swap}} + \underbrace{2n}_{\text{normalise}} + \underbrace{2n \cdot n}_{\text{eliminate}} \Big) + \underbrace{2n^{2}}_{\text{no-pivot columns}} + \underbrace{2n^{2}}_{\text{cleanup}} = 2n^{3} + 15n^{2}$$

- The check `r(i, i) != 1`: $n$.
- Copying out into `inv`: zero-fill $n^{2}$ and a loop of $n \cdot n$ iterations: $2n^{2}$.

$$T(n) \le \underbrace{n^{2}}_{\text{biggest\_abs}} + \underbrace{3n^{2} + n}_{\text{build } w} + \underbrace{2n^{3} + 15n^{2}}_{\text{echelon}} + \underbrace{n}_{\text{check}} + \underbrace{2n^{2}}_{\text{copy out}} = 2n^{3} + 21n^{2} + 2n \in O(n^{3})$$

The dominant part is the elimination on the double-width matrix, $n \cdot n \cdot 2n = 2n^{3}$. The factor 2 and the lower terms are dropped.

Space: `w` holds $2n^{2}$ numbers, the working copy inside `row_echelon` (returned as `r`) another $2n^{2}$, and `inv` holds $n^{2}$:

$$S(n) = 2n^{2} + 2n^{2} + n^{2} = 5n^{2} \in O(n^{2})$$

Subject limit: time $O(n^{3})$, space $O(n^{2})$. Both are met.

### ex13 - Rank

**Goal.** Count how many independent rows (equivalently, columns) a matrix has: the dimension of the space its map can reach. A square matrix is invertible exactly when its rank equals its size.

**What it does.**

| Input | Output |
|---|---|
| `[[1, 2, 0, 0], [2, 4, 0, 0], [-1, 2, 1, 1]]` | `2` (row 2 is twice row 1) |
| `[[1, 2, 3], [4, 5, 6], [7, 8, 9]]` | `2` (reduced form has one zero row, see ex10) |
| `[[1, 2], [3, 4]]` | `2` |

**Formula.**

$$\mathrm{rank}(A) = \text{number of non-zero rows of } \mathrm{rref}(A)$$

Reading: reduce with ex10 and count the rows that still contain something other than zero.

**Code** (`include/Matrix.hpp`, lines 277-292):

```cpp
    size_t rank() const{
        Matrix<K> r = this->row_echelon();
        size_t count = 0;
        for (size_t i = 0; i < r.rows(); i++){
            bool non_zero_row = false;
            for (size_t j = 0; j < r.cols(); j++){
                if (r(i, j) != K(0)){
                    non_zero_row = true;
                    break;
                }
            }
            if (non_zero_row)
                count++;
        }
        return count;
    }
```

Exact comparison with 0 is safe because `row_echelon` already sets every number below the tolerance to an exact 0.

#### Complexity (proof)

Let $n = \max(\text{rows}, \text{cols})$, as in ex10. The function calls `row_echelon` once and then counts. Time:

- `row_echelon()`: $n^{3} + 7n^{2}$ (the ex10 proof).
- The counting loop over `i` runs `rows` $\le n$ times and the inner loop over `j` runs `cols` $\le n$ times per row (it stops early at the first non-zero number, which only makes it cheaper), with one comparison inside: at most $n \cdot n$ operations.

$$T(n) \le \underbrace{n^{3} + 7n^{2}}_{\text{row\_echelon}} + \underbrace{n^{2}}_{\text{count}} = n^{3} + 8n^{2} \in O(n^{3})$$

The counting pass is quadratic and is dropped next to the cubic elimination.

Space: the reduced copy `r` holds $n^{2}$ numbers; `count` and the flags are single values. So $S(n) = n^{2} \in O(n^{2})$.

Subject limit: time $O(n^{3})$, space N/A. The time bound is met.

## Repository layout

| Path | What |
|---|---|
| `include/Vector.hpp` | `Vector<K>`, `ft_abs`, `check_finite`, `linear_combination`, `angle_cos`, `cross_product`, operators, printing |
| `include/Matrix.hpp` | `Matrix<K>`: add/sub/scl, `mul_vec`, `mul_mat`, `trace`, `transpose`, `row_echelon`, `determinant`, `inverse`, `rank` |
| `include/lerp.hpp` | `lerp` (generic and `float` specialisation) |
| `exNN/main.cpp` | one test program per exercise (subject examples, extra inputs, edge cases); `make` builds `exNN/test` |
| `Makefile` | `all`, `clean`, `fclean`, `re`; flags `-Wall -Wextra -Werror -std=c++11 -O2 -I include` |
| `.gitignore` | ignores the object files and test binaries |
| `README.md` | this file |

## Summary table

| Exercise | Function(s) | Time | Space |
|---|---|---|---|
| ex00 | `Vector::add`, `sub`, `scl`; `Matrix::add`, `sub`, `scl` | $O(n)$ | $O(1)$ extra |
| ex01 | `linear_combination` | $O(n)$ | $O(n)$ |
| ex02 | `lerp` | $O(n)$ | $O(n)$ |
| ex03 | `Vector::dot` | $O(n)$ | $O(1)$ |
| ex04 | `Vector::norm_1`, `norm`, `norm_inf` | $O(n)$ | $O(1)$ |
| ex05 | `angle_cos` | $O(n)$ | $O(n)$ |
| ex06 | `cross_product` | $O(1)$ | $O(1)$ |
| ex07 | `Matrix::mul_vec` | $O(nm)$ | $O(m)$ |
| ex07 | `Matrix::mul_mat` | $O(nmp)$ | $O(mp)$ |
| ex08 | `Matrix::trace` | $O(n)$ | $O(1)$ |
| ex09 | `Matrix::transpose` | $O(nm)$ | $O(nm)$ |
| ex10 | `Matrix::row_echelon` | $O(n^{3})$ | $O(n^{2})$ |
| ex11 | `Matrix::determinant` | $O(n^{3})$ | $O(n^{2})$ |
| ex12 | `Matrix::inverse` | $O(n^{3})$ | $O(n^{2})$ |
| ex13 | `Matrix::rank` | $O(n^{3})$ | $O(n^{2})$ |
