#ifndef HESTON_UNDERLYING_PROCESS_H
#define HESTON_UNDERLYING_PROCESS_H

#include <complex>

#include "fundamental_types.h"

namespace heston {

using complex_d = std::complex<double>;

/* base class for jump-diffusive process */

class base_jump_process {
 public:
  virtual complex_d evaluate(const complex_d &) const = 0;
};

class base_diffusive_process {
 public:
  virtual complex_d evaluate(const complex_d &, const double) const = 0;
  virtual double get_interest_rate() const = 0;
  virtual double get_init_vol() const = 0;
  virtual double get_init_price() const = 0;
};

class underlying_process {
 public:
  underlying_process(const base_diffusive_process &diffusive,
                     const base_jump_process &jump)
      : diffusive(diffusive), jump(jump) {}
  complex_d evaluate(const complex_d &z, const double t) const {
    return jump.evaluate(z) * diffusive.evaluate(z, t);
  }

  double get_interest_rate() const { return diffusive.get_interest_rate(); }
  double get_init_vol() const { return diffusive.get_init_vol(); }
  double get_init_price() const { return diffusive.get_init_price(); }

 private:
  const base_diffusive_process &diffusive;
  const base_jump_process &jump;
};

/* diffusive process */
template <typename diffusive_t>
class diffusive_process : public base_diffusive_process {
 public:
  diffusive_process(const diffusive_t &params) : diffusive_params(params) {}
  virtual complex_d evaluate(const complex_d &,
                             const double) const override final;

  virtual double get_init_vol() const override final {
    return diffusive_params.init_vol;
  }
  virtual double get_init_price() const override final {
    return diffusive_params.init_price;
  }
  virtual double get_interest_rate() const override final {
    return diffusive_params.interest_rate;
  }

 private:
  diffusive_t diffusive_params;
};

/* jump process */

template <typename jump_t>
class jump_process : public base_jump_process {
 public:
  jump_process(const jump_t &params) : jump_params(params) {}
  virtual complex_d evaluate(const complex_d &) const override final;

 private:
  jump_t jump_params;
};

class no_jump : public base_jump_process {
 public:
  virtual complex_d evaluate(const complex_d &) const override final {
    return complex_d(1.0, 0);
  }
};

using gbm_process = diffusive_process<gbm_params>;
using heston_process = diffusive_process<heston_params>;
using gaussian_jump = jump_process<gaussian>;
using mixed_gaussian_jump = jump_process<mixed_gaussian>;

}  // namespace heston

#endif  // HESTON_UNDERLYING_PROCESS_H
