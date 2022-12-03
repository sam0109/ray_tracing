#ifndef SRC_VEC_H
#define SRC_VEC_H

#include <array>
#include <cmath>
#include <iostream>
#include <utility>

template <typename T, int8_t N>
class Vec {
 public:
  Vec() { e.fill(0); }

  template <typename... Ts>
  explicit Vec(Ts&&... ts) : e{std::forward<Ts>(ts)...} {
    // Ensure we're passing in the correct number of arguments
    static_assert(sizeof...(ts) == N);
  }

  T x() const {
    static_assert(N > 0);
    return e[0];
  }
  T y() const {
    static_assert(N > 1);
    return e[1];
  }
  T z() const {
    static_assert(N > 2);
    return e[2];
  }

  Vec operator-() const {
    Vec<T, N> other = *this;
    for (int64_t i = 0; i < N; ++i) {
      other[i] = -e[i];
    }
    return other;
  }

  T operator[](int64_t i) const { return e[i]; }

  T& operator[](int64_t i) { return e[i]; }

  Vec& operator+=(const Vec& v) {
    for (int64_t i = 0; i < N; ++i) {
      e[i] += v[i];
    }
    return *this;
  }

  Vec& operator*=(const T t) {
    for (auto& element : e) {
      element *= t;
    }
    return *this;
  }

  Vec& operator/=(const T t) { return *this *= 1 / t; }

  T length() const { return std::sqrt(length_squared()); }

  T length_squared() const {
    T result = 0;
    for (auto element : e) {
      result += element * element;
    }
    return result;
  }

 private:
  std::array<T, N> e = {};
};

// Type aliases for Vec
using point3 = Vec<double, 3>;  // 3D point
using color = Vec<double, 3>;   // RGB color

#endif  // SRC_VEC_H