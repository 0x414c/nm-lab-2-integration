#ifndef SIMPSONINTEGRAL_HXX
#define SIMPSONINTEGRAL_HXX


#include <cstddef>

#include <functional>
#include <stdexcept>
#include <vector>

#include "numerictypes.hxx"


namespace Math
{
  class SimpsonIntegral
  {
    public:
      SimpsonIntegral (void);
      SimpsonIntegral (
        const std::function<Float (Float, Float)>& func,
        Float x_0, Float x_n, size_t n
      ) throw (std::invalid_argument);
      SimpsonIntegral (const SimpsonIntegral& that);
      SimpsonIntegral (SimpsonIntegral&& that);


      const std::function<Float (Float, Float)>& func (void) const;

      Float x_0 (void) const;
      Float x_n (void) const;

      size_t n (void) const;


      const SimpsonIntegral& operator = (const SimpsonIntegral& that);
      const SimpsonIntegral& operator = (SimpsonIntegral&& that);

      Float operator () (Float u) const;


      constexpr static Float Theta_Inv = 15;


    private:
      std::function<Float (Float, Float)> func_;

      Float x_0_;
      Float x_n_;

      size_t n_;

      Float h_;

      std::vector<Float> x_;
  };
}

#endif // SIMPSONINTEGRAL_HXX
