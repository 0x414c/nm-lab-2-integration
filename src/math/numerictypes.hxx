#ifndef NUMERICTYPES_HXX
#define NUMERICTYPES_HXX


#ifdef QUAD_PRECISION_ENABLED
#include <boost/multiprecision/float128.hpp>
#endif // QUAD_PRECISION_ENABLED


namespace Math
{
#ifdef QUAD_PRECISION_ENABLED
#define REAL_T_IS_BOOST_FLOAT128
#else
//#define REAL_T_IS_GCC_FLOAT80
//#define REAL_T_IS_LONG_DOUBLE
#define REAL_T_IS_DOUBLE
//#define REAL_T_IS_FLOAT
#endif // QUAD_PRECISION_ENABLED


#ifdef REAL_T_IS_BOOST_FLOAT128
#define REAL_C(x) (x ## Q)
  using real_t = boost::multiprecision::float128;
#else
#ifdef REAL_T_IS_GCC_FLOAT80
#define REAL_C(x) (x ## W)
  using real_t = __float80;
#else
#ifdef REAL_T_IS_LONG_DOUBLE
#define REAL_C(x) (x ## L)
  using real_t = long double;
#else
#ifdef REAL_T_IS_DOUBLE
#define REAL_C(x) (x)
  using real_t = double;
#else
#ifdef REAL_T_IS_FLOAT
#define REAL_C(x) (x ## F)
  using real_t = float;
#else
#error "`real_t' alias was not defined due to absence of `REAL_T_IS_*' macro."
#error "`REAL_C(x)' macro was not defined too!"
#endif // REAL_IS_FLOAT
#endif // REAL_IS_DOUBLE
#endif // REAL_IS_LONG_DOUBLE
#endif // REAL_IS_GCC_FLOAT80
#endif // REAL_IS_BOOST_FLOAT128
}


#endif // NUMERICTYPES_HXX
