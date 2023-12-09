#ifndef HESTON_CALCULATOR_H
#define HESTON_CALCULATOR_H

#include "fundamental_types.h"
#include "underlying_process.h"

namespace heston {
class calculator {
 public:
  double calc_option_price(const instrument_data&, const underlying_process&,
                           const double) const;

 private:
  double stepsize = 0.4;
  double alpha = 1.5;
  double max_range = 2000.0;
};

}  // namespace heston

#endif  // HESTON_CALCULATOR_H
