#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix/unmanaged/Unmanaged.h"

#include <pybind11/pybind11.h>


void feed_enable(int i) {
  ctre::phoenix::unmanaged::Unmanaged::FeedEnable(i);
}

void set_phoenix_diagnostics_start_time(int i) {
  ctre::phoenix::unmanaged::Unmanaged::SetPhoenixDiagnosticsStartTime(i);
}

/*
 * I couldn't figure out how to use pybind11 directly on the TalonSRX, the subclassing
 * seemed to get in the way. Wrapping seems expedient.
 */
class TalonSRXWrapper
{
  public:
    TalonSRXWrapper(int id) : t{id} {}
    ~TalonSRXWrapper() {}
    int get_device_id() { return t.GetDeviceID(); }
    void set_power(double power) { t.Set(ControlMode::PercentOutput, power); }
    double get_output_current() { return t.GetOutputCurrent(); }
    double get_position() { return t.GetSelectedSensorPosition(); }
    bool is_fwd_limit_switch_closed() { return t.IsFwdLimitSwitchClosed() != 0; }
    bool is_rev_limit_switch_closed() { return t.IsRevLimitSwitchClosed() != 0; }
    void set_brake(bool brake) { t.SetNeutralMode(brake ? NeutralMode::Brake : NeutralMode::Coast); }

  private:
    TalonSRX t;
};

namespace py = pybind11;

PYBIND11_MODULE(PyPhoenix5, m) {
  // optional module docstring
  m.doc() = "CTRE Phoenix5 example plugin";

  m.def("feed_enable", &feed_enable, "Feed the watchdog");

  m.def("set_phoenix_diagnostics_start_time", &set_phoenix_diagnostics_start_time, "Set the delay for starting the diagnostics server");

  py::class_<TalonSRXWrapper>(m, "TalonSRX")
    .def(py::init<int>())
    .def("get_device_id", &TalonSRXWrapper::get_device_id)
    .def("set_power", &TalonSRXWrapper::set_power)
    .def("get_output_current", &TalonSRXWrapper::get_output_current)
    .def("get_position", &TalonSRXWrapper::get_position)
    .def("is_fwd_limit_switch_closed", &TalonSRXWrapper::is_fwd_limit_switch_closed)
    .def("is_rev_limit_switch_closed", &TalonSRXWrapper::is_rev_limit_switch_closed)
    .def("set_brake", &TalonSRXWrapper::set_brake)
    ;
}
