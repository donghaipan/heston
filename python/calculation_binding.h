#include <pybind11/pybind11.h>

#include <complex>

#include <black76.h>
#include <calculator.h>
#include <fundamental_types.h>
#include <underlying_process.h>

namespace py = pybind11;

void init_calculation_binding(py::module &m) {
  // types
  py::enum_<heston::option_t>(m, "option_t")
      .value("call", heston::option_t::call)
      .value("put", heston::option_t::put);

  py::class_<heston::instrument_data>(m, "instrument_data")
      .def(py::init<>())
      .def_readwrite("strike", &heston::instrument_data::strike)
      .def_readwrite("call_put", &heston::instrument_data::call_put);

  py::class_<heston::gbm_params>(m, "gbm_params")
      .def(py::init<>())
      .def_readwrite("interest_rate", &heston::gbm_params::interest_rate)
      .def_readwrite("init_vol", &heston::gbm_params::init_vol)
      .def_readwrite("init_price", &heston::gbm_params::init_price);

  py::class_<heston::heston_params, heston::gbm_params>(m, "heston_params")
      .def(py::init<>())
      .def_readwrite("kappa", &heston::heston_params::kappa)
      .def_readwrite("theta", &heston::heston_params::theta)
      .def_readwrite("xi", &heston::heston_params::xi)
      .def_readwrite("rho", &heston::heston_params::rho);

  py::class_<heston::gaussian>(m, "gaussian")
      .def(py::init<>())
      .def_readwrite("mu", &heston::gaussian::mu)
      .def_readwrite("sigma", &heston::gaussian::sigma);

  py::class_<heston::mixed_gaussian>(m, "mixed_gaussian")
      .def(py::init<>())
      .def_readwrite("prob_up", &heston::mixed_gaussian::prob_up)
      .def_readwrite("up_mv", &heston::mixed_gaussian::up_mv)
      .def_readwrite("down_mv", &heston::mixed_gaussian::down_mv);

  // black76
  m.def("b76_price", &heston::b76_price, "calculate black76 price");
  m.def("calc_implied_vol", &heston::calc_implied_vol,
        "calculate implied volatility given option price");

  // calculator
  py::class_<heston::calculator>(m, "calculator")
      .def(py::init<>())
      .def("calc_option_price", &heston::calculator::calc_option_price);
}
