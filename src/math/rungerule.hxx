#ifndef RUNGERULE_HXX
#define RUNGERULE_HXX


#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <iostream>
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
      RungeRule (const TIntegral& integral, Float epsilon) :
        integral_n_ (integral),
        n_max_ (integral_n_.n ()),
        epsilon_ (epsilon)
      { }


      Float
      operator () (Float u)
      {
        TIntegral integral_2n (
          integral_n_.func (), integral_n_.x_0 (), integral_n_.x_n (),
          integral_n_.n () * 2
        );

        std::cerr << '\t' << integral_n_.n () << ' ' << integral_2n.n () << ' ' << n_max_ << '\n';

        Float I_n (integral_n_ (u));
        Float I_2n (integral_2n (u));
        Float delta_2n (std::abs (I_2n - I_n) / TIntegral::Theta_Inv);

        while (isGreaterThan (delta_2n, epsilon_))
        {
          integral_n_ = std::move (integral_2n);
          integral_2n = TIntegral (
            integral_n_.func (), integral_n_.x_0 (), integral_n_.x_n (),
            integral_n_.n () * 2
          );

//          std::cerr << '!' << integral_n_.n () << ' ' << integral_2n.n () << '\n';

          I_n = integral_n_ (u) ;
          I_2n = integral_2n (u);
          delta_2n = (std::abs (I_2n - I_n) / TIntegral::Theta_Inv);
        }

        n_max_ = std::max (n_max_, integral_2n.n ());

        return I_2n;
      }


      size_t n_max (void) const
      {
        std::cerr << n_max_ << '\n';

        return n_max_;
      }


    private:
      TIntegral integral_n_;

      size_t n_max_;

      Float epsilon_;
  };
}

#endif // RUNGERULE_HXX
