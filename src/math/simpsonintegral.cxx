#include <cstddef>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#ifdef QUAD_PRECISION_ENABLED
#include <boost/math/special_functions/fpclassify.hpp>
#endif // QUAD_PRECISION_ENABLED

#include "simpsonintegral.hxx"
#include "mathutils.hxx"
#include "numerictypes.hxx"


namespace Math
{
  SimpsonIntegral::SimpsonIntegral (void)
  { }


  SimpsonIntegral::SimpsonIntegral (
    const std::function<Float (Float, Float)>& func,
    Float x_0, Float x_n_1, size_t n
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

    x_ = std::vector <Float> (2 * n_ + 1);

    h_ = ((x_n_ - x_0_) / Float (2 * n_));

    for (size_t k (0); k < 2 * n_ + 1; ++k)
    {
      x_[k] = x_0_ + Float (k) * h_;
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


  const std::function<Float (Float, Float)>&
  SimpsonIntegral::func() const
  {
    return func_;
  }


  Float
  SimpsonIntegral::x_0 (void) const
  {
    return x_0_;
  }


  Float
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


  Float
  SimpsonIntegral::operator () (Float u) const
  {
    Float sum (0), correction (0);

    for (size_t k (0); k < 2 * n_; k += 2)
    {
      const Float term (
        func_ (x_[k], u) +
        Float (4) * func_ (x_[k + 1], u) +
        func_ (x_[k + 2], u)
      );

#ifdef QUAD_PRECISION_ENABLED
      if (boost::math::isnan (term))
#else
      if (std::isnan (term))
#endif // QUAD_PRECISION_ENABLED
      {
        continue;
      }
      else
      {
        const Float correctedNextTerm (term - correction);
        const Float newSum (sum + correctedNextTerm);
        correction = (newSum - sum) - correctedNextTerm;
        sum = newSum;
      }
    }

    return (sum / Float (3) * h_);
  }
}
