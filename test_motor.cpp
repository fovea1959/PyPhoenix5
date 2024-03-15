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
