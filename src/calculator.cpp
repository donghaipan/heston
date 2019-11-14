#include "calculator.h"
#include "fundamental_types.h"
#include "underlying_process.h"

namespace heston {
// TODO: the following is only call_price;
double calculator::calc_option_price(const instrument_data& inst_data,
                                     const underlying_process& ul_process,
                                     const double voltime) const {
  const auto strike = inst_data.strike;
  const auto interest_rate = ul_process.get_interest_rate();
  const auto unit_im = complex_d(0.0, 1.0);
  const double log_strike = std::log(strike);
  double res = 0;
  for (double j = -max_range; j < max_range; j = j + stepsize) {
    complex_d z(j, -alpha);
    auto tmp = ul_process.evaluate(z - unit_im, voltime) *
               std::exp(-log_strike * unit_im * z) / (z * unit_im - z * z);
    res += tmp.real() * stepsize;
  }
  return 0.5 * res * std::exp(-voltime * interest_rate) / M_PI;
};
}  // namespace heston
