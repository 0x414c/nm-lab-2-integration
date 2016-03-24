#ifndef REAL_T_IS_BOOST_FLOAT128
#include <cmath>
#endif // REAL_T_IS_BOOST_FLOAT128

#include "functions.hxx"
#include "numerictypes.hxx"


namespace Math
{
  real_t
  f (
    real_t x,
    real_t alpha, real_t beta, real_t gamma, real_t delta, real_t epsilon, real_t mu
  )
  {
#ifdef REAL_T_IS_BOOST_FLOAT128
    return (
      alpha * boost::multiprecision::sin (beta / boost::multiprecision::pow (x - gamma, REAL_C (2))) +
      delta * boost::multiprecision::cos (epsilon / boost::multiprecision::pow (x - mu, REAL_C (2)))
    );

//    return (
//      alpha * (boost::multiprecision::sin (boost::multiprecision::tan (beta / (x - gamma)))) +
//      delta * (boost::multiprecision::cos (epsilon * x))
//    );
#else
    return (
      alpha * std::sin (beta / std::pow (x - gamma, REAL_C (2))) +
      delta * std::cos (epsilon / std::pow (x - mu, REAL_C (2)))
    );

//    return (
//      alpha * (std::sin (std::tan (beta / (x - gamma)))) +
//      delta * (std::cos (epsilon * x))
//    );
#endif // REAL_T_IS_BOOST_FLOAT128
  }
}
