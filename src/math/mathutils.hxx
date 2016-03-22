#ifndef MATHUTILS_HXX
#define MATHUTILS_HXX


#include "numerictypes.hxx"


namespace Math
{
  // TODO: [~-] Inline?
  Float lerp (Float x1, Float y1, Float x2, Float y2, Float x0);

  Float clamp (Float a, Float b, Float x);

  bool isGreaterThan (Float x, Float y);
}


#endif // MATHUTILS_HXX
