#ifndef cetlib_hypot_h
#define cetlib_hypot_h

// ======================================================================
//
// hypot: Checked and unchecked Euclidean planar hypotenuse calculations
//
// ======================================================================

#include <cmath>
#include <limits>
#include <type_traits>
#include <utility>

#include "cetlib_except/cxx20_macros.h"
#if CET_CONCEPTS_AVAILABLE
#include "cetlib/detail/cetlib_concepts.h"
#include <concepts>
#endif
// ----------------------------------------------------------------------

namespace cet {
  template <class T>
#if CET_CONCEPTS_AVAILABLE
    requires(detail::is_arithmetic<T>)
  T
#else
  std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
    hypot(T x, T y);

  template <class T>
#if CET_CONCEPTS_AVAILABLE
    requires(detail::is_arithmetic<T>)
  T
#else
  std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
    unchecked_hypot(T x, T y);

  template <class T>
#if CET_CONCEPTS_AVAILABLE
    requires(detail::is_arithmetic<T>)
  T
#else
  std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
    checked_hypot(T x, T y);
}

// ----------------------------------------------------------------------
// unchecked_hypot<>:

template <class T>
#if CET_CONCEPTS_AVAILABLE
  requires(cet::detail::is_arithmetic<T>)
inline T
#else
inline std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
  cet::unchecked_hypot(T x, T y)
{
  return std::hypot(x, y);
}

// ----------------------------------------------------------------------
// checked_hypot<>:

template <class T>
#if CET_CONCEPTS_AVAILABLE
  requires(cet::detail::is_arithmetic<T>)
T
#else
std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
  cet::checked_hypot(T x, T y)
{

  if (std::isinf(x) || std::isinf(y))
    return std::numeric_limits<T>::infinity();
  else if (std::isnan(x) || std::isnan(y))
    return std::numeric_limits<T>::quiet_NaN();
  else
    return unchecked_hypot(x, y);

} // checked_hypot<>(,)

// ----------------------------------------------------------------------
// hypot<>:

template <class T>
#if CET_CONCEPTS_AVAILABLE
  requires(cet::detail::is_arithmetic<T>)
inline T
#else
inline std::enable_if_t<std::is_arithmetic_v<T>, T>
#endif
  cet::hypot(T x, T y)
{
  return checked_hypot(x, y);
}

#endif /* cetlib_hypot_h */

// Local Variables:
// mode: c++
// End:
