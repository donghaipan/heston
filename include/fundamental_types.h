#ifndef HESTON_FUNDAMENTAL_TYPES_H
#define HESTON_FUNDAMENTAL_TYPES_H

#include <cassert>
#include <cmath>

namespace heston {

enum class option_t { call, put };

struct instrument_data {
  instrument_data() {}
  instrument_data(const double strike_, const option_t call_put_)
      : strike(strike_), call_put(call_put_) {}

  double strike;
  option_t call_put;
};

struct gbm_params {
  gbm_params() {}
  gbm_params(const double interest_rate_, const double init_vol_,
             const double init_price_)
      : interest_rate(interest_rate_),
        init_vol(init_vol_),
        init_price(init_price_) {}

  double interest_rate;
  double init_vol;
  double init_price;
};

struct heston_params : public gbm_params {
  heston_params(){};
  heston_params(double interest_rate_, double init_vol_, double init_price_,
                double kappa_, double theta_, double xi_, double rho_)
      : gbm_params(interest_rate_, init_vol_, init_price_),
        kappa(kappa_),
        theta(theta_),
        xi(xi_),
        rho(rho_) {}

  /* for greek letter meaning, see wikipage */
  double kappa;  // mean-reversion rate
  double theta;  // long term variance
  double xi;     // vol of vol
  double rho;    // correlation
};

struct jumpless {};

struct gaussian {
  gaussian(){};
  gaussian(const double mu_, const double sigma_) : mu(mu_), sigma(sigma_) {}
  gaussian(const double sigma_) : sigma(sigma_) { mu = -0.5 * sigma * sigma; }

  double mu;
  double sigma;
};

struct mixed_gaussian {
  mixed_gaussian(){};
  mixed_gaussian(const double prob_up_, const gaussian& up_mv_,
                 const gaussian& down_mv_)
      : prob_up(prob_up_), up_mv(up_mv_), down_mv(down_mv_) {}
  mixed_gaussian(const gaussian& up_mv_, const gaussian& down_mv_) {
    double prob = 0.0;
    double up_mean = std::exp(up_mv_.mu + 0.5 * up_mv_.sigma * up_mv_.sigma);
    double down_mean =
        std::exp(down_mv_.mu + 0.5 * down_mv_.sigma * down_mv_.sigma);

    if (up_mean == down_mean) {
      prob = 0.5;
    } else {
      prob = (1 - down_mean) / (up_mean - down_mean);
    }
    assert(prob >= 0.0 && prob <= 1.0);
    prob_up = prob;
    up_mv = up_mv_;
    down_mv = down_mv_;
  }

  double prob_up;
  gaussian up_mv;
  gaussian down_mv;
};

}  // namespace heston

#endif  // HESTON_FUNDAMENTAL_TYPES_H
