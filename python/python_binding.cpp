#include <pybind11/pybind11.h>

#include "calculation_binding.h"
#include "underlying_process_binding.h"

namespace py = pybind11;

PYBIND11_MODULE(heston, m) {
  init_calculation_binding(m);
  init_underlying_process_binding(m);
}
