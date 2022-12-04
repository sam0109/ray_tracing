#ifndef SRC_VEC_H
#define SRC_VEC_H

#include <array>
#include <cmath>
#include <iostream>
#include <utility>

#include "absl/functional/function_ref.h"
#include "absl/strings/str_join.h"

struct NoneTag {};
struct ColorTag {};
struct SpaceTag {};

template <typename T, int8_t N, typename Tag = NoneTag>
class Vec {
 public:
  Vec() { e.fill(0); }

  template <typename OtherTag>
  Vec(const Vec<T, N, OtherTag> &other) {
    std::copy(other.cbegin(), other.cend(), e.begin());
  }

  template <
      typename... Ts,
      std::enable_if_t<(std::is_same_v<T, absl::remove_cvref_t<Ts>> && ...),
                       bool> = true>
  explicit Vec(Ts... ts) : e{ts...} {
    // Ensure we're passing in the correct number of arguments
    static_assert(sizeof...(ts) == N);
  }

  T X() const {
    static_assert(N > 0 && std::is_same_v<Tag, SpaceTag>);
    return e[0];
  }
  T Y() const {
    static_assert(N > 1 && std::is_same_v<Tag, SpaceTag>);
    return e[1];
  }
  T Z() const {
    static_assert(N > 2 && std::is_same_v<Tag, SpaceTag>);
    return e[2];
  }
  T R() const {
    static_assert(N > 0 && std::is_same_v<Tag, ColorTag>);
    return e[0];
  }
  T G() const {
    static_assert(N > 1 && std::is_same_v<Tag, ColorTag>);
    return e[1];
  }
  T B() const {
    static_assert(N > 2 && std::is_same_v<Tag, ColorTag>);
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

  Vec &ZipOnto(absl::FunctionRef<T(T, T)> f, Vec<T, N, Tag> other) {
    for (int8_t i = 0; i < N; ++i) {
      e[i] = f(e[i], other[i]);
    }
    return *this;
  }

  Vec Zip(absl::FunctionRef<T(T, T)> f, Vec<T, N, Tag> other) const {
    Vec<T, N, Tag> result = *this;
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
using Point = Vec<double, 3, SpaceTag>;  // 3D point
using Color = Vec<double, 3, ColorTag>;  // RGB color
using Vec3 = Vec<double, 3, SpaceTag>;   // Regular old vector

template <typename T, int8_t N, typename Tag>
auto begin(const Vec<T, N, Tag> &v) {
  return v.cbegin();
}

template <typename T, int8_t N, typename Tag>
auto end(const Vec<T, N, Tag> &v) {
  return v.cend();
}

template <typename T, int8_t N, typename Tag>
std::ostream &operator<<(std::ostream &out, const Vec<T, N, Tag> &v) {
  return out << absl::StrJoin(v, " ");
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator+(const Vec<T, N, Tag> &u, const Vec<T, N, Tag> &v) {
  return u.Zip([](T l, T r) { return l + r; }, v);
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator-(const Vec<T, N, Tag> &u, const Vec<T, N, Tag> &v) {
  return u.Zip([](T l, T r) { return l - r; }, v);
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator*(const Vec<T, N, Tag> &u, const Vec<T, N, Tag> &v) {
  return u.Zip([](T l, T r) { return l * r; }, v);
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator*(T t, const Vec<T, N, Tag> &v) {
  return v.Map([t](T e) { return t * e; });
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator*(const Vec<T, N, Tag> &v, double t) {
  return t * v;
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> operator/(Vec<T, N, Tag> v, double t) {
  return (1 / t) * v;
}

template <typename T, int8_t N, typename Tag>
double dot(const Vec<T, N, Tag> &u, const Vec<T, N, Tag> &v) {
  return (u * v).template Accumulate<T>(
      [](T acc, T e) -> T { return acc + e; });
}

template <typename T, typename Tag>
Vec<T, 3, Tag> cross(const Vec<T, 3, Tag> &u, const Vec<T, 3, Tag> &v) {
  return Vec<T, 3>(u.Y() * v.Z() - u.Z() * v.Y(), u.Z() * v.X() - u.X() * v.Z(),
                   u.X() * v.Y() - u.Y() * v.X());
}

template <typename T, int8_t N, typename Tag>
Vec<T, N, Tag> unit_vector(Vec<T, N, Tag> v) {
  return v / v.length();
}

#endif  // SRC_VEC_H