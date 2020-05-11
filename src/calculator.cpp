#include <calculator.h>
#include <fundamental_types.h>
#include <underlying_process.h>

namespace heston {
double calculator::calc_option_price(const instrument_data& inst_data,
                                     const underlying_process& ul_process,
                                     const double voltime) const {
  const auto strike = inst_data.strike;
  const auto init_price = ul_process.get_init_price();
  const auto interest_rate = ul_process.get_interest_rate();
  const auto unit_im = complex_d(0.0, 1.0);
  const auto log_strike = std::log(strike);
  double res = 0;
  for (double j = -max_range; j < max_range; j = j + stepsize) {
    complex_d z(j, -alpha);
    auto tmp = ul_process.evaluate(z - unit_im, voltime) *
               std::exp(-log_strike * unit_im * z) / (z * unit_im - z * z);
    res += tmp.real() * stepsize;
  }
  double discount = std::exp(-voltime * interest_rate);
  return 0.5 * discount * res / M_PI - (inst_data.call_put == option_t::put) *
                                           (init_price - discount * strike);
};
}  // namespace heston
