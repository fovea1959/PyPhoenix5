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
    int get_last_error() { return t.GetLastError(); }
    int set_power(double power) { 
      t.Set(ControlMode::PercentOutput, power);
      return t.GetLastError();
    }
    double get_output_current() { return t.GetOutputCurrent(); }
    double get_position() { return t.GetSelectedSensorPosition(); }
    bool is_fwd_limit_switch_closed() { return t.IsFwdLimitSwitchClosed() != 0; }
    bool is_rev_limit_switch_closed() { return t.IsRevLimitSwitchClosed() != 0; }
    int set_brake(bool brake) { 
      t.SetNeutralMode(brake ? NeutralMode::Brake : NeutralMode::Coast);
      return t.GetLastError();
    }
    std::string hi_bob() { return "Hi, Bob!"; }

  private:
    TalonSRX t;
};

std::string errtext(int i){
  switch(i) {
    case ctre::phoenix::OK: // 0
      return "OK";
    case ctre::phoenix::CAN_MSG_STALE: // 1
      return "CAN_MSG_STALE";
    case ctre::phoenix::CAN_TX_FULL: // -1
      return "CAN_TX_FULL";
    case ctre::phoenix::CAN_INVALID_PARAM: // -2
      return "CAN_INVALID_PARAM";
    case ctre::phoenix::CAN_MSG_NOT_FOUND: // -3
      return "CAN_MSG_NOT_FOUND";
    case ctre::phoenix::CAN_NO_MORE_TX_JOBS: // -4
      return "CAN_NO_MORE_TX_JOBS";
    case ctre::phoenix::CAN_NO_SESSIONS_AVAIL: // -5
      return "CAN_NO_SESSIONS_AVAIL";
    case ctre::phoenix::CAN_OVERFLOW: // -6
      return "CAN_OVERFLOW";
    case ctre::phoenix::SensorNotPresent: // -7
      return "SensorNotPresent";
    case ctre::phoenix::FirmwareTooOld: // -8
      return "FirmwareTooOld";
    case ctre::phoenix::CouldNotChangePeriod: // -9
      return "CouldNotChangePeriod";
    case ctre::phoenix::BufferFailure: // -10
      return "BufferFailure";
    case ctre::phoenix::FirwmwareNonFRC: // -11
      return "FirwmwareNonFRC";
    case ctre::phoenix::GENERAL_ERROR: // -100
      return "GENERAL_ERROR";
    case ctre::phoenix::SIG_NOT_UPDATED: // -200
      return "SIG_NOT_UPDATED";
    case ctre::phoenix::NotAllPIDValuesUpdated: // -201
      return "NotAllPIDValuesUpdated";
    case ctre::phoenix::GEN_PORT_ERROR: // -300
      return "GEN_PORT_ERROR";
    case ctre::phoenix::PORT_MODULE_TYPE_MISMATCH: // -301
      return "PORT_MODULE_TYPE_MISMATCH";
    case ctre::phoenix::GEN_MODULE_ERROR: // -400
      return "GEN_MODULE_ERROR";
    case ctre::phoenix::MODULE_NOT_INIT_SET_ERROR: // -401
      return "MODULE_NOT_INIT_SET_ERROR";
    case ctre::phoenix::MODULE_NOT_INIT_GET_ERROR: // -402
      return "MODULE_NOT_INIT_GET_ERROR";
    case ctre::phoenix::WheelRadiusTooSmall: // -500
      return "WheelRadiusTooSmall";
    case ctre::phoenix::TicksPerRevZero: // -501
      return "TicksPerRevZero";
    case ctre::phoenix::DistanceBetweenWheelsTooSmall: // -502
      return "DistanceBetweenWheelsTooSmall";
    case ctre::phoenix::GainsAreNotSet: // -503
      return "GainsAreNotSet";
    case ctre::phoenix::WrongRemoteLimitSwitchSource: // -504
      return "WrongRemoteLimitSwitchSource";
    case ctre::phoenix::DoubleVoltageCompensatingWPI: // -505
      return "DoubleVoltageCompensatingWPI";
    case ctre::phoenix::CANdleAnimSlotOutOfBounds: // -506
      return "CANdleAnimSlotOutOfBounds";
    case ctre::phoenix::IncompatibleMode: // -600
      return "IncompatibleMode";
    case ctre::phoenix::InvalidHandle: // -601
      return "InvalidHandle";
    case ctre::phoenix::FeatureRequiresHigherFirm: // -700
      return "FeatureRequiresHigherFirm";
    case ctre::phoenix::MotorControllerFeatureRequiresHigherFirm: // -701
      return "MotorControllerFeatureRequiresHigherFirm";
    case ctre::phoenix::ConfigFactoryDefaultRequiresHigherFirm: // -702
      return "ConfigFactoryDefaultRequiresHigherFirm";
    case ctre::phoenix::ConfigMotionSCurveRequiresHigherFirm: // -703
      return "ConfigMotionSCurveRequiresHigherFirm";
    case ctre::phoenix::TalonFXFirmwarePreVBatDetect: // -704
      return "TalonFXFirmwarePreVBatDetect";
    case ctre::phoenix::CANdleAnimationsRequireHigherFirm: // -705
      return "CANdleAnimationsRequireHigherFirm";
    case ctre::phoenix::LibraryCouldNotBeLoaded: // -800
      return "LibraryCouldNotBeLoaded";
    case ctre::phoenix::MissingRoutineInLibrary: // -801
      return "MissingRoutineInLibrary";
    case ctre::phoenix::ResourceNotAvailable: // -802
      return "ResourceNotAvailable";
    case ctre::phoenix::MusicFileNotFound: // -900
      return "MusicFileNotFound";
    case ctre::phoenix::MusicFileWrongSize: // -901
      return "MusicFileWrongSize";
    case ctre::phoenix::MusicFileTooNew: // -902
      return "MusicFileTooNew";
    case ctre::phoenix::MusicFileInvalid: // -903
      return "MusicFileInvalid";
    case ctre::phoenix::InvalidOrchestraAction: // -904
      return "InvalidOrchestraAction";
    case ctre::phoenix::MusicFileTooOld: // -905
      return "MusicFileTooOld";
    case ctre::phoenix::MusicInterrupted: // -906
      return "MusicInterrupted";
    case ctre::phoenix::MusicNotSupported: // -907
      return "MusicNotSupported";
    case ctre::phoenix::kInvalidInterface: // -1000
      return "kInvalidInterface";
    case ctre::phoenix::kInvalidGuid: // -1001
      return "kInvalidGuid";
    case ctre::phoenix::kInvalidClass: // -1002
      return "kInvalidClass";
    case ctre::phoenix::kInvalidProtocol: // -1003
      return "kInvalidProtocol";
    case ctre::phoenix::kInvalidPath: // -1004
      return "kInvalidPath";
    case ctre::phoenix::kGeneralWinUsbError: // -1005
      return "kGeneralWinUsbError";
    case ctre::phoenix::kFailedSetup: // -1006
      return "kFailedSetup";
    case ctre::phoenix::kListenFailed: // -1007
      return "kListenFailed";
    case ctre::phoenix::kSendFailed: // -1008
      return "kSendFailed";
    case ctre::phoenix::kReceiveFailed: // -1009
      return "kReceiveFailed";
    case ctre::phoenix::kInvalidRespFormat: // -1010
      return "kInvalidRespFormat";
    case ctre::phoenix::kWinUsbInitFailed: // -1011
      return "kWinUsbInitFailed";
    case ctre::phoenix::kWinUsbQueryFailed: // -1012
      return "kWinUsbQueryFailed";
    case ctre::phoenix::kWinUsbGeneralError: // -1013
      return "kWinUsbGeneralError";
    case ctre::phoenix::kAccessDenied: // -1014
      return "kAccessDenied";
    case ctre::phoenix::kFirmwareInvalidResponse: // -1015
      return "kFirmwareInvalidResponse";
    case ctre::phoenix::PulseWidthSensorNotPresent: // +10
      return "PulseWidthSensorNotPresent";
    case ctre::phoenix::GeneralWarning: // 100
      return "GeneralWarning";
    case ctre::phoenix::FeatureNotSupported: // 101
      return "FeatureNotSupported";
    case ctre::phoenix::NotImplemented: // 102
      return "NotImplemented";
    case ctre::phoenix::FirmVersionCouldNotBeRetrieved: // 103
      return "FirmVersionCouldNotBeRetrieved";
    case ctre::phoenix::FeaturesNotAvailableYet: // 104
      return "FeaturesNotAvailableYet";
    case ctre::phoenix::ControlModeNotValid: // 105
      return "ControlModeNotValid";
    case ctre::phoenix::ControlModeNotSupportedYet: // 106
      return "ControlModeNotSupportedYet";
    case ctre::phoenix::CascadedPIDNotSupporteYet: // 107
      return "CascadedPIDNotSupporteYet";
    case ctre::phoenix::RemoteSensorsNotSupportedYet: // 108
      return "RemoteSensorsNotSupportedYet";
    case ctre::phoenix::MotProfFirmThreshold: // 109
      return "MotProfFirmThreshold";
    case ctre::phoenix::MotProfFirmThreshold2: // 110
      return "MotProfFirmThreshold2";
    case ctre::phoenix::SimDeviceNotFound: // 200
      return "SimDeviceNotFound";
    case ctre::phoenix::SimPhysicsTypeNotSupported: // 201
      return "SimPhysicsTypeNotSupported";
    case ctre::phoenix::SimDeviceAlreadyExists: // 202
      return "SimDeviceAlreadyExists";
    default:
      return "!!!!!!!!!!!!!!!!";
  }
}

namespace py = pybind11;

PYBIND11_MODULE(PyPhoenix5, m) {
  // optional module docstring
  m.doc() = "CTRE Phoenix5 example plugin";

  m.def("feed_enable", &feed_enable, "Feed the watchdog");

  m.def("set_phoenix_diagnostics_start_time", &set_phoenix_diagnostics_start_time, "Set the delay for starting the diagnostics server");

  py::class_<TalonSRXWrapper>(m, "TalonSRX")
    .def(py::init<int>())
    .def("get_device_id", &TalonSRXWrapper::get_device_id)
    .def("get_last_error", &TalonSRXWrapper::get_last_error)
    .def("set_power", &TalonSRXWrapper::set_power)
    .def("get_output_current", &TalonSRXWrapper::get_output_current)
    .def("get_position", &TalonSRXWrapper::get_position)
    .def("is_fwd_limit_switch_closed", &TalonSRXWrapper::is_fwd_limit_switch_closed)
    .def("is_rev_limit_switch_closed", &TalonSRXWrapper::is_rev_limit_switch_closed)
    .def("set_brake", &TalonSRXWrapper::set_brake)
    .def("hi_bob", &TalonSRXWrapper::hi_bob)
    ;

  m.def("get_error_text", &errtext, "Return the error text for a given code");

}
