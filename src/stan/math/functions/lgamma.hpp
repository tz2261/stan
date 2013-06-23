#ifndef __STAN__MATH__FUNCTIONS__LGAMMA_HPP__
#define __STAN__MATH__FUNCTIONS__LGAMMA_HPP__

#include <boost/math/special_functions/gamma.hpp>

namespace stan {

  namespace math {

    // throws domain_error if x is at pole
    double lgamma(double x) {
      return boost::math::lgamma(x);
    }

  }
}

#endif
