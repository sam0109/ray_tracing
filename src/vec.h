#ifndef SRC_VEC_H
#define SRC_VEC_H

#include <array>
#include <cmath>
#include <iostream>
#include <utility>

#include "absl/functional/function_ref.h"
#include "absl/strings/str_join.h"

template <typename T, int8_t N>
class Vec {
 public:
  Vec() { e.fill(0); }

  template <typename... Ts>
  explicit Vec(Ts &&...ts) : e{std::forward<Ts>(ts)...} {
    // Ensure we're passing in the correct number of arguments
    static_assert(sizeof...(ts) == N);
  }

  T X() const {
    static_assert(N > 0);
    return e[0];
  }
  T Y() const {
    static_assert(N > 1);
    return e[1];
  }
  T Z() const {
    static_assert(N > 2);
    return e[2];
  }

  Vec &MapOnto(absl::FunctionRef<T(T)> f) {
    for (auto &element : e) {
      element = f(element);
    }
    return *this;
  }

  Vec Map(absl::FunctionRef<T(T)> f) const {
    Vec other = *this;
    other.MapOnto(f);
    return other;
  }

  Vec &ZipOnto(absl::FunctionRef<T(T, T)> f, Vec<T, N> other) {
    for (int8_t i = 0; i < N; ++i) {
      e[i] = f(e[i], other[i]);
    }
    return *this;
  }

  Vec Zip(absl::FunctionRef<T(T, T)> f, Vec<T, N> other) const {
    Vec<T, N> result = *this;
    result.ZipOnto(f, other);
    return result;
  }

  template <typename Acc>
  Acc Accumulate(absl::FunctionRef<Acc(Acc, T)> f) const {
    Acc result{};
    for (auto element : e) {
      result = f(result, element);
    }
    return result;
  }

  Vec operator-() const {
    return Map([](T e) { return -e; });
  }

  T operator[](int8_t i) const { return e[i]; }

  T &operator[](int8_t i) { return e[i]; }

  auto begin() { return e.begin(); }

  auto cbegin() const { return e.begin(); }

  auto end() { return e.end(); }

  auto cend() const { return e.end(); }

  Vec &operator+=(const Vec &v) {
    return ZipOnto([](T l, T r) { return l + r; }, v);
  }

  Vec &operator*=(const T t) {
    return MapOnto([t](T e) { return e * t; });
  }

  Vec &operator/=(const T t) {
    return MapOnto([t](T e) { return e / t; });
  }

  T length() const { return std::sqrt(length_squared()); }

  T length_squared() const {
    return Accumulate<T>([](T acc, T val) { return acc + (val * val); });
  }

 private:
  std::array<T, N> e = {};
};

// Type aliases for Vec
using point3 = Vec<double, 3>;  // 3D point
using color = Vec<double, 3>;   // RGB color

template <typename T, int8_t N>
auto begin(const Vec<T, N> &v) {
  return v.cbegin();
}

template <typename T, int8_t N>
auto end(const Vec<T, N> &v) {
  return v.cend();
}

template <typename T, int8_t N>
std::ostream &operator<<(std::ostream &out, const Vec<T, N> &v) {
  return out << absl::StrJoin(v, " ");
}

template <typename T, int8_t N>
Vec<T, N> operator+(const Vec<T, N> &u, const Vec<T, N> &v) {
  return u.Zip([](T l, T r) { return l + r; }, v);
}

template <typename T, int8_t N>
Vec<T, N> operator-(const Vec<T, N> &u, const Vec<T, N> &v) {
  return u.Zip([](T l, T r) { return l - r; }, v);
}

template <typename T, int8_t N>
Vec<T, N> operator*(const Vec<T, N> &u, const Vec<T, N> &v) {
  return u.Zip([](T l, T r) { return l * r; }, v);
}

template <typename T, int8_t N>
Vec<T, N> operator*(T t, const Vec<T, N> &v) {
  return v.Map([t](T e) { return t * e; });
}

template <typename T, int8_t N>
Vec<T, N> operator*(const Vec<T, N> &v, double t) {
  return t * v;
}

template <typename T, int8_t N>
Vec<T, N> operator/(Vec<T, N> v, double t) {
  return (1 / t) * v;
}

template <typename T, int8_t N>
double dot(const Vec<T, N> &u, const Vec<T, N> &v) {
  return (u * v).Accumulate([](T acc, T e) { acc + e; });
}

template <typename T>
Vec<T, 3> cross(const Vec<T, 3> &u, const Vec<T, 3> &v) {
  return Vec<T, 3>(u.Y() * v.Z() - u.Z() * v.Y(), u.Z() * v.X() - u.X() * v.Z(),
                   u.X() * v.Y() - u.Y() * v.X());
}

template <typename T, int8_t N>
Vec<T, N> unit_vector(Vec<T, N> v) {
  return v / v.length();
}

#endif  // SRC_VEC_H