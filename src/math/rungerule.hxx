#ifndef RUNGERULE_HXX
#define RUNGERULE_HXX


#include "../globaldefines.hxx"

#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN
#include <cstddef>

#include <algorithm>
#include <functional>
#include <utility>

#include "simpsonintegral.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"


namespace Math
{
  template<typename TIntegral = SimpsonIntegral>
  class RungeRule
  {
    public:
      RungeRule (void) = delete;

      RungeRule (const TIntegral& integral, real_t epsilon) :
        integral_n_ (integral),
        n_max_ (integral_n_.n ()),
        epsilon_ (epsilon)
      { }


      real_t
      operator () (real_t u)
      {
        TIntegral integral_2n (
          integral_n_.func (), integral_n_.x_0 (), integral_n_.x_n (),
          integral_n_.n () * 2
        );

        real_t I_n (integral_n_ (u));
        real_t I_2n (integral_2n (u));
#ifdef REAL_IS_BOOST_FLOAT128
        real_t delta_2n (boost::multiprecision::abs (I_2n - I_n) / TIntegral::Theta_Inv);
#else
        real_t delta_2n (std::abs (I_2n - I_n) / TIntegral::Theta_Inv);
#endif // REAL_IS_BOOST_FLOAT128

        while (isGreaterThan (delta_2n, epsilon_))
        {
          integral_n_ = std::move (integral_2n);
          integral_2n = TIntegral (
            integral_n_.func (), integral_n_.x_0 (), integral_n_.x_n (),
            integral_n_.n () * 2
          );

          I_n = integral_n_ (u);
          I_2n = integral_2n (u);
#ifdef REAL_IS_BOOST_FLOAT128
          delta_2n = (boost::multiprecision::abs (I_2n - I_n) / TIntegral::Theta_Inv);
#else
          delta_2n = (std::abs (I_2n - I_n) / TIntegral::Theta_Inv);
#endif // REAL_IS_BOOST_FLOAT128
        }

        n_max_ = std::max (n_max_, integral_2n.n ());

        return I_2n;
      }


      size_t
      n_max (void) const
      {
        return n_max_;
      }


    private:
      TIntegral integral_n_;

      size_t n_max_;

      real_t epsilon_;
  };
}

#endif // RUNGERULE_HXX
