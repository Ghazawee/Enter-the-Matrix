#ifndef LERP_HPP
#define LERP_HPP

#include "Vector.hpp"
#include "Matrix.hpp"

// Linear interpolation between two values: keep (1 - t) of u and take t of v.
// Same result as u + (v - u) * t, but v - u can overflow (FLT_MAX - (-FLT_MAX) = inf)
// while this form never goes above the bigger of u and v when t is between 0 and 1.
// ex02. n = number of coordinates in u (1 for a float).
// Time O(n): two scalings and one addition, each one pass. Space O(n): u * (1 - t) and v * t are temporary copies.
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

#endif
