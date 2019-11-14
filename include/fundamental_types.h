#ifndef HESTON_FUNDAMENTAL_TYPES_H
#define HESTON_FUNDAMENTAL_TYPES_H

namespace heston {

enum class option_t { call, put };

struct instrument_data {
  double strike;
  option_t call_put;
};

struct gbm_params {
  double interest_rate;
  double init_vol;
  double init_price;
};

struct heston_params : public gbm_params {
  /* for greek letter meaning, see wikipage */
  double kappa;
  double theta;
  double xi;
};

struct gaussian {
  double mu;
  double sigma;
};

struct mixed_gaussian {
  double prob_up;
  gaussian up_mv;
  gaussian down_mv;
};

}  // namespace heston

#endif  // HESTON_FUNDAMENTAL_TYPES_H
