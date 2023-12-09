#include <pybind11/pybind11.h>

#include <complex>

#include "heston/fundamental_types.h"
#include "heston/underlying_process.h"

namespace py = pybind11;

class py_base_jump_process : public heston::base_jump_process {
 public:
  using heston::base_jump_process::base_jump_process;

  std::complex<double> evaluate(const std::complex<double> &z) const override {
    PYBIND11_OVERLOAD_PURE(std::complex<double>, heston::base_jump_process,
                           evaluate, z);
  }
};

class py_base_diffusive_process : public heston::base_diffusive_process {
 public:
  using heston::base_diffusive_process::base_diffusive_process;

  std::complex<double> evaluate(const std::complex<double> &z,
                                const double t) const override {
    PYBIND11_OVERLOAD_PURE(std::complex<double>, heston::base_diffusive_process,
                           evaluate, z, t);
  }

  double get_interest_rate() const override {
    PYBIND11_OVERLOAD_PURE(double, heston::base_diffusive_process,
                           get_interest_rate, );
  }

  double get_init_vol() const override {
    PYBIND11_OVERLOAD_PURE(double, heston::base_diffusive_process,
                           get_init_vol, );
  }

  double get_init_price() const override {
    PYBIND11_OVERLOAD_PURE(double, heston::base_diffusive_process,
                           get_init_price, );
  }
};

void init_underlying_process_binding(py::module &m) {
  // binding for jump process
  py::class_<heston::base_jump_process, py_base_jump_process>(
      m, "base_jump_process")
      .def(py::init<>())
      .def("evaluate", &heston::base_jump_process::evaluate);

  py::class_<heston::no_jump, heston::base_jump_process>(m, "no_jump")
      .def(py::init<const heston::jumpless &>());

  py::class_<heston::gaussian_jump, heston::base_jump_process>(m,
                                                               "gaussian_jump")
      .def(py::init<const heston::gaussian &>());

  py::class_<heston::mixed_gaussian_jump, heston::base_jump_process>(
      m, "mixed_gaussian_jump")
      .def(py::init<const heston::mixed_gaussian &>());

  // binding diffusive process
  py::class_<heston::base_diffusive_process, py_base_diffusive_process>(
      m, "base_diffusive_process")
      .def(py::init<>())
      .def("evaluate", &heston::base_diffusive_process::evaluate)
      .def("get_init_vol", &heston::base_diffusive_process::get_init_vol)
      .def("get_init_price", &heston::base_diffusive_process::get_init_price)
      .def("get_interest_rate",
           &heston::base_diffusive_process::get_interest_rate);

  py::class_<heston::gbm_process, heston::base_diffusive_process>(m,
                                                                  "gbm_process")
      .def(py::init<const heston::gbm_params &>());

  py::class_<heston::heston_process, heston::base_diffusive_process>(
      m, "heston_process")
      .def(py::init<const heston::heston_params &>());

  // underlying processes
  py::class_<heston::underlying_process>(m, "underlying_process")
      .def(py::init<heston::base_diffusive_process &,
                    heston::base_jump_process &>())
      .def("evaluate", &heston::underlying_process::evaluate)
      .def("get_interest_rate", &heston::underlying_process::get_interest_rate)
      .def("get_init_vol", &heston::underlying_process::get_init_vol)
      .def("get_init_price", &heston::underlying_process::get_init_price);
}
