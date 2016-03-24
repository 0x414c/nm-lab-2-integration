#include "../globaldefines.hxx"

#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN

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
#ifdef REAL_IS_BOOST_FLOAT128
    return (
      alpha * boost::multiprecision::sin (beta / boost::multiprecision::pow (x - gamma, REAL_EXTERNAL_C (2.))) +
      delta * boost::multiprecision::cos (epsilon / boost::multiprecision::pow (x - mu, REAL_EXTERNAL_C (2.)))
    );
#else
    return (
      alpha * std::sin (beta / std::pow (x - gamma, REAL_BUILTIN_C (2.))) +
      delta * std::cos (epsilon / std::pow (x - mu, REAL_BUILTIN_C (2.)))
    );
#endif // REAL_IS_BOOST_FLOAT128
  }
}
