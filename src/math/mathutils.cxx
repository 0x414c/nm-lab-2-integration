#ifndef REAL_T_IS_BOOST_FLOAT128
#include <cmath>
#endif // REAL_T_IS_BOOST_FLOAT128

#include <algorithm>

#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  real_t
  lerp (real_t x1, real_t y1, real_t x2, real_t y2, real_t x0)
  {
    return (y1 + (y2 - y1) * ((x0 - x1) / (x2 - x1)));
  }


  real_t
  clamp (real_t a, real_t b, real_t x)
  {
    return std::max (a, std::min (b, x));
  }


  bool
  isGreaterThan (real_t x, real_t y)
  {
    return (
      (x - y) >
      Config::MathConstants::Epsilon * std::max<real_t> ({
#ifdef REAL_T_IS_BOOST_FLOAT128
        REAL_C (1), boost::multiprecision::abs (x), boost::multiprecision::abs (y)
#else
        REAL_C (1), std::abs (x), std::abs (y)
#endif // REAL_T_IS_BOOST_FLOAT128
      })
    );
  }
}
