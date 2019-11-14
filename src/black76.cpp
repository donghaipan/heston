#include <cmath>
#include <stdexcept>

#include "black76.h"
#include "fundamental_types.h"

// double normal_pdf(const double x) {
//  return exp(-0.5 * x * x) * M_SQRT1_2 * sqrt(M_1_PI);
//};

namespace heston {

double normal_cdf(const double x) { return 0.5 * erfc(-x * M_SQRT1_2); };

double d_plus(const double strike, const double fwd_price,
              const double vol_sqrt_time) {
  return log(fwd_price / strike) / vol_sqrt_time + 0.5 * vol_sqrt_time;
};

double b76_price(const double strike, const double fwd_price,
                 const double voltime, const double ivol,
                 const double interest_rate, const option_t option_type) {
  double vol_sqrt_time = ivol * std::sqrt(voltime);
  double is_put = (option_type == option_t::put);

  if (vol_sqrt_time < 1E-6) {
    return (fwd_price > strike ? (fwd_price - strike) : 0.0) -
           is_put * (fwd_price - strike);
  } else {
    double d1 = d_plus(strike, fwd_price, vol_sqrt_time);
    double d2 = d1 - vol_sqrt_time;
    double discount = std::exp(-interest_rate * voltime);
    return discount * (fwd_price * normal_cdf(d1) - strike * normal_cdf(d2) -
                       is_put * (fwd_price - strike));
  }
};

double calc_implied_vol(const double strike, const double forward,
                        const double voltime, const double interest_rate,
                        const double option_price, const option_t option_type) {
  double lower_bd = 0.0;
  double upper_bd = 1.0;
  int count = 0;
  double est = b76_price(strike, forward, voltime, (lower_bd + upper_bd) / 2,
                         interest_rate, option_type);
  while (std::abs(est - option_price) > 1E-8) {
    if (est > option_price) {
      upper_bd = (lower_bd + upper_bd) / 2;
    } else {
      lower_bd = (lower_bd + upper_bd) / 2;
    }
    est = b76_price(strike, forward, voltime, (lower_bd + upper_bd) / 2,
                    interest_rate, option_type);
    count++;
    if (count > 2000) {
      throw std::runtime_error("Implied vol solver does not converge.");
    }
  }
  return (lower_bd + upper_bd) / 2;
};

}  // namespace heston
