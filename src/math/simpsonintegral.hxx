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
        const std::function<real_t (real_t, real_t)>& func,
        real_t x_0, real_t x_n, size_t n
      ) throw (std::invalid_argument);
      SimpsonIntegral (const SimpsonIntegral& that);
      SimpsonIntegral (SimpsonIntegral&& that);


      const std::function<real_t (real_t, real_t)>& func (void) const;

      real_t x_0 (void) const;
      real_t x_n (void) const;

      size_t n (void) const;


      const SimpsonIntegral& operator= (const SimpsonIntegral& that);
      const SimpsonIntegral& operator= (SimpsonIntegral&& that);

      real_t operator() (real_t u) const;


      static constexpr real_t Theta_Inv = REAL_C (15.);


    private:
      std::function<real_t (real_t, real_t)> func_;

      real_t x_0_;
      real_t x_n_;

      size_t n_;

      real_t h_;

      std::vector<real_t> x_;
  };
}

#endif // SIMPSONINTEGRAL_HXX
