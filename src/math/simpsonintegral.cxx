#include "../globaldefines.hxx"

#ifdef REAL_IS_BUILTIN
#include <cmath>
#endif // REAL_IS_BUILTIN
#include <cstddef>

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

#ifdef REAL_IS_BOOST_FLOAT128
#include <boost/math/special_functions/fpclassify.hpp>
#endif // REAL_IS_BOOST_FLOAT128

#include "simpsonintegral.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"


namespace Math
{
  SimpsonIntegral::SimpsonIntegral (void)
  { }


  SimpsonIntegral::SimpsonIntegral (
    const std::function<real_t (real_t, real_t)>& func,
    real_t x_0, real_t x_n_1, size_t n
  ) throw (std::invalid_argument) :
    func_ (func),
    x_0_ (x_0),
    x_n_ (x_n_1),
    n_ (n)
  {
    if (n_ < 1)
    {
      throw std::invalid_argument ("`n' should be greater than 0.");
    }

    if (x_0_ >= x_n_)
    {
      throw std::invalid_argument ("`x_0' should be less than `x_n'.");
    }

    x_ = std::vector <real_t> (2 * n_ + 1);

    h_ = (x_n_ - x_0_) / real_t (2 * n_);

    for (size_t k (0); k < 2 * n_ + 1; ++k)
    {
      x_[k] = x_0_ + real_t (k) * h_;
    }
  }


  SimpsonIntegral::SimpsonIntegral (const SimpsonIntegral& that) :
    func_ (that.func_),
    x_0_ (that.x_0_),
    x_n_ (that.x_n_),
    n_ (that.n_),
    h_ (that.h_),
    x_ (that.x_)
  { }


  SimpsonIntegral::SimpsonIntegral (SimpsonIntegral&& that) :
    func_ (std::move (that.func_)),
    x_0_ (that.x_0_),
    x_n_ (that.x_n_),
    n_ (that.n_),
    h_ (that.h_),
    x_ (std::move (that.x_))
  { }


  const std::function<real_t (real_t, real_t)>&
  SimpsonIntegral::func() const
  {
    return func_;
  }


  real_t
  SimpsonIntegral::x_0 (void) const
  {
    return x_0_;
  }


  real_t
  SimpsonIntegral::x_n (void) const
  {
    return x_n_;
  }


  size_t
  SimpsonIntegral::n (void) const
  {
    return n_;
  }


  const SimpsonIntegral&
  SimpsonIntegral::operator = (const SimpsonIntegral& that)
  {
    if (this != &that)
    {
      func_ = that.func_;
      x_0_ = that.x_0_;
      x_n_ = that.x_n_;
      n_ = that.n_;
      h_ = that.h_;
      x_ = that.x_;
    }

    return *this;
  }


  const SimpsonIntegral&
  SimpsonIntegral::operator = (SimpsonIntegral&& that)
  {
    if (this != &that)
    {
      func_ = std::move (that.func_);
      x_0_ = that.x_0_;
      x_n_ = that.x_n_;
      n_ = that.n_;
      h_ = that.h_;
      x_ = std::move (that.x_);
    }

    return *this;
  }


  real_t
  SimpsonIntegral::operator () (real_t u) const
  {
    real_t sum (0), correction (0);

    for (size_t k (0); k < 2 * n_; k += 2)
    {
      const real_t term (
        func_ (x_[k], u) +
        REAL_C (4.) * func_ (x_[k + 1], u) +
        func_ (x_[k + 2], u)
      );

#ifdef REAL_IS_BOOST_FLOAT128
      if (boost::math::isnan (term))
#else
      if (std::isnan (term))
#endif // REAL_IS_BOOST_FLOAT128
      {
        continue;
      }
      else
      {
        const real_t correctedNextTerm (term - correction);
        const real_t newSum (sum + correctedNextTerm);
        correction = (newSum - sum) - correctedNextTerm;
        sum = newSum;
      }
    }

    return (sum / REAL_C (3.) * h_);
  }
}
