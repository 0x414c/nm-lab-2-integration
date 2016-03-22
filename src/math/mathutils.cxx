#include <cmath>

#include <algorithm>

#include "mathutils.hxx"
#include "numerictypes.hxx"
#include "../config.hxx"


namespace Math
{
  Float
  lerp (Float x1, Float y1, Float x2, Float y2, Float x0)
  {
    return (y1 + (y2 - y1) * ((x0 - x1) / (x2 - x1)));
  }


  Float
  clamp (Float a, Float b, Float x)
  {
    return std::max (a, std::min (b, x));
  }


  bool
  isGreaterThan (Float x, Float y)
  {
    return (
      (x - y) >
      Config::MathConstants::Epsilon * std::max<Float> ({
        Float (1), std::abs (x), std::abs (y)
      })
    );
  }
}
