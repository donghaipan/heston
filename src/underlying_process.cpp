#include "underlying_process.h"
#include "fundamental_types.h"

namespace heston {

inline complex_d gaussian_char_func(const gaussian& params,
                                    const complex_d& z) {
  return std::exp(complex_d(0.0, params.mu) * z -
                  0.5 * params.sigma * params.sigma * z * z);
}

template <>
complex_d gaussian_jump::evaluate(const complex_d& z) const {
  return gaussian_char_func(jump_params, z);
}

template <>
complex_d mixed_gaussian_jump::evaluate(const complex_d& z) const {
  const auto prob_up = jump_params.prob_up;
  const auto& up_mv = jump_params.up_mv;
  const auto& down_mv = jump_params.down_mv;
  return prob_up * gaussian_char_func(up_mv, z) +
         (1.0 - prob_up) * gaussian_char_func(down_mv, z);
}

template <>
complex_d gbm_process::evaluate(const complex_d& z,
                                const double voltime) const {
  const auto init_price = get_init_price();
  const auto interest_rate = get_interest_rate();
  const auto init_vol = get_init_vol();

  auto interest_tte = voltime * interest_rate;
  auto vol_square_tte = init_vol * init_vol * voltime;
  auto log_px = std::log(init_price);
  auto linear_term = interest_tte + log_px - 0.5 * vol_square_tte;
  return std::exp(linear_term * complex_d(0, 1) * z -
                  0.5 * vol_square_tte * z * z);
}

template <>
complex_d heston_process::evaluate(const complex_d& z,
                                   const double voltime) const {
  const auto kappa = diffusive_params.kappa;
  const auto theta = diffusive_params.theta;
  const auto xi = diffusive_params.xi;
  const auto rho = diffusive_params.rho;

  const auto log_px = std::log(get_init_price());
  const auto rate = get_interest_rate();
  const auto ivol = get_init_vol();

  const auto vol_square = ivol * ivol;
  auto z_sq_z = (z * z) + z * complex_d(0, 1);
  auto kappa_z = kappa - z * complex_d(0, rho * xi);
  auto gamma = std::sqrt((kappa_z * kappa_z) + z_sq_z * xi * xi);
  auto em = exp(gamma * -voltime);
  auto tm0 = z * complex_d(0, log_px + rate * voltime);
  auto tm1 =
      (voltime * (kappa_z - gamma) -
       2.0 * std::log(1.0 + 0.5 * (kappa_z - gamma) * (1.0 - em) / gamma)) *
      kappa * theta / (xi * xi);
  auto tm2 = -vol_square * z_sq_z * (1.0 - em) /
           (2.0 * gamma * em + (gamma + kappa_z) * (1.0 - em));
  return exp(tm0 + tm1 + tm2);
}

}  // namespace heston
