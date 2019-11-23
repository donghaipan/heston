#include <pybind11/pybind11.h>

#include <complex>
#include <sstream>

#include <black76.h>
#include <calculator.h>
#include <fundamental_types.h>
#include <underlying_process.h>

#include "repr_helpers.h"

namespace py = pybind11;

void init_calculation_binding(py::module &m) {
  // types
  py::enum_<heston::option_t>(m, "option_t")
      .value("call", heston::option_t::call)
      .value("put", heston::option_t::put)
      .def("__repr__", [](const heston::option_t &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::instrument_data>(m, "instrument_data")
      .def(py::init<>())
      .def(py::init<const double, const heston::option_t>(), py::arg("strike"),
           py::arg("call_put"))
      .def_readwrite("strike", &heston::instrument_data::strike)
      .def_readwrite("call_put", &heston::instrument_data::call_put)
      .def("__repr__", [](const heston::instrument_data &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::gbm_params>(m, "gbm_params")
      .def(py::init<>())
      .def(py::init<const double, const double, const double>(),
           py::arg("interest_rate"), py::arg("init_vol"), py::arg("init_price"))
      .def_readwrite("interest_rate", &heston::gbm_params::interest_rate)
      .def_readwrite("init_vol", &heston::gbm_params::init_vol)
      .def_readwrite("init_price", &heston::gbm_params::init_price)
      .def("__repr__", [](const heston::gbm_params &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::heston_params, heston::gbm_params>(m, "heston_params")
      .def(py::init<>())
      .def(py::init<const double, const double, const double, const double,
                    const double, const double, const double>(),
           py::arg("interest_rate"), py::arg("init_vol"), py::arg("init_price"),
           py::arg("kappa"), py::arg("theta"), py::arg("xi"), py::arg("rho"))
      .def_readwrite("kappa", &heston::heston_params::kappa)
      .def_readwrite("theta", &heston::heston_params::theta)
      .def_readwrite("xi", &heston::heston_params::xi)
      .def_readwrite("rho", &heston::heston_params::rho)
      .def("__repr__", [](const heston::heston_params &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::jumpless>(m, "jumpless")
      .def(py::init<>())
      .def("__repr__", [](const heston::jumpless &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::gaussian>(m, "gaussian")
      .def(py::init<>())
      .def(py::init<const double>(), py::arg("sigma"))
      .def(py::init<const double, const double>(), py::arg("mu"),
           py::arg("sigma"))
      .def_readwrite("mu", &heston::gaussian::mu)
      .def_readwrite("sigma", &heston::gaussian::sigma)
      .def("__repr__", [](const heston::gaussian &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  py::class_<heston::mixed_gaussian>(m, "mixed_gaussian")
      .def(py::init<>())
      .def(py::init<const heston ::gaussian &, const heston::gaussian &>(),
           py::arg("up_mv"), py::arg("down_mv"))
      .def(py::init<const double, const heston ::gaussian &,
                    const heston::gaussian &>(),
           py::arg("prob_up"), py::arg("up_mv"), py::arg("down_mv"))
      .def_readwrite("prob_up", &heston::mixed_gaussian::prob_up)
      .def_readwrite("up_mv", &heston::mixed_gaussian::up_mv)
      .def_readwrite("down_mv", &heston::mixed_gaussian::down_mv)
      .def("__repr__", [](const heston::mixed_gaussian &obj) {
        std::ostringstream os;
        os << obj;
        return os.str();
      });

  // black76
  m.def("b76_price", &heston::b76_price, "calculate black76 price",
        py::arg("strike"), py::arg("fwd_price"), py::arg("voltime"),
        py::arg("ivol"), py::arg("interest_rate"), py::arg("option_type"));
  m.def("calc_implied_vol", &heston::calc_implied_vol,
        "calculate implied volatility given option price", py::arg("strike"),
        py::arg("fwd_px"), py::arg("voltime"), py::arg("interest_rate"),
        py::arg("option_price"), py::arg("call_put"));

  // calculator
  py::class_<heston::calculator>(m, "calculator")
      .def(py::init<>())
      .def("calc_option_price", &heston::calculator::calc_option_price,
           py::arg("inst_data"), py::arg("ul_process"), py::arg("voltime"));
}
