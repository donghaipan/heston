#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_calculation_binding(py::module&);
void init_underlying_process_binding(py::module&);

PYBIND11_MODULE(heston, m) {
  init_calculation_binding(m);
  init_underlying_process_binding(m);
}
