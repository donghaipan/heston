#include <ostream>

#include <fundamental_types.h>

std::ostream& operator<<(std::ostream& os, const heston::option_t& obj) {
  os << "option_t.";
  if (obj == heston::option_t::call) {
    os << "call";
  } else {
    os << "put";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::instrument_data& obj) {
  os << "instrument_data(strike: " << obj.strike << ", "
     << "call_put: " << obj.call_put << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::gbm_params& obj) {
  os << "gbm_params(interest_rate: " << obj.interest_rate << ", "
     << "init_vol: " << obj.init_vol << ", "
     << "init_price: " << obj.init_price << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::heston_params& obj) {
  os << "heston_params(interest_rate: " << obj.interest_rate << ", "
     << "init_vol: " << obj.init_vol << ", "
     << "init_price: " << obj.init_price << ", "
     << "kappa: " << obj.kappa << ", "
     << "theta: " << obj.theta << ", "
     << "xi: " << obj.xi << ", "
     << "rho: " << obj.rho << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::jumpless& obj) {
  os << "jumpless()";
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::gaussian& obj) {
  os << "gaussian("
     << "mu: " << obj.mu << ", "
     << "sigma: " << obj.sigma << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const heston::mixed_gaussian& obj) {
  os << "mixed_gaussian("
     << "prob_up: " << obj.prob_up << ", "
     << "up_mv: " << obj.up_mv << ", ";
  os << "down_mv: " << obj.down_mv << ")";
  return os;
}
