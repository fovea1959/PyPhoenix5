#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix/unmanaged/Unmanaged.h"

#include <pybind11/pybind11.h>

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include <unistd.h>

int add(int i, int j) {
    return i + j;
}

class Pet
{
    public:
        Pet(const std::string &name, int hunger) : name(name), hunger(hunger) {}
        ~Pet() {}

        void go_for_a_walk() { hunger++; }
        const std::string &get_name() const { return name; }
        int get_hunger() const { return hunger; }

    private:
        std::string name;
        int hunger;
};

void feed_enable(int i) {
	ctre::phoenix::unmanaged::Unmanaged::FeedEnable(i);
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

    private:
	TalonSRX t;
};

namespace py = pybind11;

PYBIND11_MODULE(PyPhoenix5, m) {
    // optional module docstring
    m.doc() = "CTRE Phoenix5 example plugin";

    // define add function
    m.def("add", &add, "A function which adds two numbers");

    // bindings to Pet class
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &, int>())
        .def("go_for_a_walk", &Pet::go_for_a_walk)
        .def("get_hunger", &Pet::get_hunger)
        .def("get_name", &Pet::get_name);

    m.def("feed_enable", &feed_enable, "Feed the watchdog");

    py::class_<TalonSRXWrapper>(m, "TalonSRX")
	.def(py::init<int>())
	.def("get_device_id", &TalonSRXWrapper::get_device_id)
	.def("set_power", &TalonSRXWrapper::set_power);
}



#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

/* make some talons for drive train */
std::string interface = "can0";
// TalonSRX talLeft(1, interface); //Use the specified interface
TalonSRX talLeft(1);

/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void goFor1S(double power)
{
	for (int i = 0; i < 50; i++) {
		talLeft.Set(ControlMode::PercentOutput, power);
		ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);

		double current = talLeft.GetOutputCurrent();
		double position = talLeft.GetSelectedSensorPosition(0);
		int f = talLeft.IsFwdLimitSwitchClosed();
		int b = talLeft.IsRevLimitSwitchClosed();
		printf("output current = %f, position = %f, f=%d, b=%d\n", current, position, f, b);

		/* loop yield for a bit */
		sleepApp(20);
	}
}



int main() {	
	// Comment out the call if you would rather use the automatically running diag-server, note this requires uninstalling diagnostics from Tuner. 
	// c_SetPhoenixDiagnosticsStartTime(-1); // disable diag server, instead we will use the diag server stand alone application that Tuner installs

	printf ("device id = %d", talLeft.GetDeviceID());
	while (true) {
		talLeft.SetNeutralMode(NeutralMode::Brake);
		goFor1S(0.2);
		goFor1S(0.0);
		goFor1S(-0.2);
		goFor1S(0.0);
		talLeft.SetNeutralMode(NeutralMode::Coast);
		goFor1S(0.2);
		goFor1S(0.0);
		goFor1S(-0.2);
		goFor1S(0.0);
		while (true) {
			goFor1S(0.0);
		}
	}
	talLeft.Set(ControlMode::PercentOutput, 0.0);

	return 0;
}

