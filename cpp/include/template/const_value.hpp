#include "includes.hpp"

#pragma once

namespace sub {
template <typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
inf_sub() {
  return std::numeric_limits<T>::max() / 2 - 1000;
}

template <typename T>
constexpr typename std::enable_if<std::is_floating_point<T>::value, T>::type
inf_sub() {
  return std::min(std::numeric_limits<T>::max() / 2 - 1000, T(1e50));
}
}  // namespace sub

/// @return Returns a large finite value representable by the numeric type T.
/// @note It is guaranteed that the return values is strictly less than std::numeric_limits<T>::max() / 2.
template <typename T> constexpr T inf() {
  static_assert(std::is_arithmetic<T>::value, "T must be arithmetic value");
  return sub::inf_sub<T>();
}

/// @return Returns the zero value representable by the numeric type T.
template <typename T> constexpr T zero() {
  static_assert(std::is_arithmetic<T>::value, "T must be arithmetic value");
  return T(0);
}

const long double pi = acos(-1.0);
