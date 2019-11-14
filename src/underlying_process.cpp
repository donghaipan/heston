#include "underlying_process.h"
#include "fundamental_types.h"

namespace heston {

template <>
complex_d gaussian_jump::evaluate(const complex_d& z) const {
  return z;
};

template <>
complex_d mixed_gaussian_jump::evaluate(const complex_d& z) const {
  return z;
};

template <>
complex_d gbm_process::evaluate(const complex_d& z, const double voltime) const {
  const auto init_price = get_init_price();
  const auto interest_rate = get_interest_rate();
  const auto init_vol = get_init_vol();

  double interest_tte = voltime * interest_rate;
  double vol_square_tte = init_vol * init_vol * voltime;
  double log_px = std::log(init_price);
  double linear_term = interest_tte + log_px - 0.5 * vol_square_tte;
  return std::exp(linear_term * complex_d(0, 1) * z -
                  0.5 * vol_square_tte * z * z);
};

template <>
complex_d heston_process::evaluate(const complex_d& z, const double t) const {
  return z;
};

}  // namespace heston
