#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  real_t lerp (real_t x1, real_t y1, real_t x2, real_t y2, real_t x0);

  real_t clamp (real_t a, real_t b, real_t x);

  bool isGreaterThan (real_t x, real_t y);
}


#endif // MATHUTILS_HXX
