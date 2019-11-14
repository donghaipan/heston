#ifndef HESTON_BLACK76_H
#define HESTON_BLACK76_H

#include "fundamental_types.h"

namespace heston {

double b76_price(const double strike, const double forward,
                 const double voltime, const double ivol,
                 const double interest_rate, const option_t option_type);

double calc_implied_vol(const double strike, const double forward,
                        const double voltime, const double interest_rate,
                        const double option_price, const option_t option_type);

}  // namespace heston

#endif  // HESTON_BLACK76_H
