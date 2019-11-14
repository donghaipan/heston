#include <iomanip>
#include <iostream>

#include "black76.h"
#include "calculator.h"
#include "fundamental_types.h"
#include "underlying_process.h"

int main() {
  double strike = 3000.0;
  double fwd_px = 2700.0;
  double interest_rate = 0.02;
  double voltime = 0.1;
  double ivol = 0.16;
  double init_px = fwd_px * std::exp(-interest_rate * voltime);
  auto option_type = heston::option_t::call;
  auto option_px = heston::b76_price(strike, fwd_px, voltime, ivol,
                                     interest_rate, option_type);
  std::cout << std::setprecision(10) << option_px << std::endl;

  heston::instrument_data inst_data = {strike, option_type};
  heston::gbm_params diff_params = {interest_rate, ivol, init_px};
  auto jump_p = heston::no_jump();
  heston::gbm_process diff_p = {diff_params};
  auto ul_p = heston::underlying_process(diff_p, jump_p);
  auto calc = heston::calculator();
  auto opt_px = calc.calc_option_price(inst_data, ul_p, voltime);
  std::cout << std::setprecision(10) << opt_px << std::endl;
  return 0;
}
