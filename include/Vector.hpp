#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <initializer_list>
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <limits>

// Absolute value (abs is not an allowed function).
template <typename K>
K ft_abs(K x) {
    return x < 0 ? -x : x;
}

// Throws if x is infinity or NaN ("not a number").
// NaN is the only value that is not equal to itself; infinity is bigger than the largest float.
template <typename K>
void check_finite(K x) {
    if (x != x || x > std::numeric_limits<K>::max() || x < -std::numeric_limits<K>::max())
        throw std::overflow_error("value is inf or nan (out of float range)");
}

// Vector<K>: a list of n scalars of type K (float for the mandatory part).
// Header-only because it's a template: the compiler must see the whole template where it is used.
template <typename K>
class Vector {
private:
    std::vector<K> _data;
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

public:
    Vector() {}
    explicit Vector(size_t n) : _data(n, K()) {}                  // n zeros
    Vector(std::initializer_list<K> list) : _data(list) {}         // Vector<float> v = {1.f, 2.f};

    size_t   size() const { return _data.size(); }
    // .at(i) checks i < size() and throws std::out_of_range, instead of reading memory that isn't ours.
    K&       operator[](size_t i)       { return _data.at(i); }
    const K& operator[](size_t i) const { return _data.at(i); }

    // ex00 add / sub / scl. n = number of coordinates.
    // Time O(n): one pass, each number visited once. Space O(1) extra: writes into this vector (subject allows O(n)).
    void add(const Vector<K>& v){
        apply(v, [](K a, K b){return a + b;}, "add: size mismatch");
    }

    void sub(const Vector<K>& v){
        apply(v, [](K a, K b){return a - b;}, "sub: size mismatch");
    }

    void    scl(K a){
        for(size_t i = 0; i < this->size(); i++){
            K value = _data[i] * a;
            check_finite(value);
            _data[i] = value;
        }
    }

    // ex03. Time O(n): one multiply-add per coordinate. Space O(1): only result.
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

    // ex04 norm_1, norm, norm_inf. Time O(n) each (norm makes two passes: norm_inf, then its loop: 2n is still O(n)).
    // Space O(1): a few floats, no copy.
    float norm_1() const{
        float total = 0.f;
        for(size_t i = 0; i < this->size(); i++){
            total += ft_abs(_data[i]);
        }
        check_finite(total);
        return total;
    }

    // Squaring 1e20 overflows (1e40 > largest float) and squaring 1e-30 rounds to 0, even though
    // the length itself fits. So: shrink every number so the biggest one is 1, measure, grow back.
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
};

template <typename K>
Vector<K> operator+(Vector<K> a, const Vector<K> &b) { a.add(b); return a; }

template <typename K>
Vector<K> operator-(Vector<K> a, const Vector<K> &b) { a.sub(b); return a; }

template <typename K>
Vector<K> operator*(Vector<K> a, K t) { a.scl(t); return a; }

// ex01. n = total number of coordinates (k vectors of size d: n = k * d).
// Time O(n): every coordinate of every vector is used once. Space O(n): the result has d numbers, d <= n.
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

// Shrinking a vector doesn't change its direction, so the angle is the same. We shrink both
// vectors until their biggest number is 1: then dot and norm can't overflow or round to 0.
// ex05. Time O(n): a fixed number of passes (2 norm_inf, 2 copies, the shrink, dot, 2 norms of 2 passes each), about 10n, still O(n).
// Space O(n): the two shrunk copies a and b.
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

// ex06. Time O(1), space O(1): always exactly 3 coordinates, 6 multiplications (the subject sets no limit).
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

// Prints like the subject: one "[x]" per line.
template <typename K>
std::ostream& operator<<(std::ostream& os, const Vector<K>& v) {
    for (size_t i = 0; i < v.size(); ++i){
        K x = v[i];
        if (x == 0)
            x = 0;   // avoid printing -0
        os << "[" << x<< "]" << std::endl;
    }
    return os;
}

#endif
