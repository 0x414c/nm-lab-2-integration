#include <cmath>

#include "functions.hxx"
#include "numerictypes.hxx"


namespace Math
{
  Float
  f (
    Float x,
    Float alpha, Float beta, Float gamma, Float delta, Float epsilon, Float mu
  )
  {
    return (
      alpha * (std::sin (std::tan (beta / (x - gamma)))) + delta * (std::cos (epsilon * x))
    );

//    return std::sin (x);

//    return (
//      alpha * std::sin (beta / std::pow (x - gamma, 2)) +
//      delta * std::cos (epsilon / std::pow (x - mu, 2))
//    );
  }
}
