#pragma once

#if __has_include(<React-Codegen/AppSpecsJSI.h>) // CocoaPod headers on Apple
#include <React-Codegen/AppSpecsJSI.h>
#elif __has_include("AppSpecsJSI.h") // CMake headers on Android
#include "AppSpecsJSI.h"
#endif
#include <memory>
#include <string>

namespace facebook::react {

#define MAX_FUEL_RAW 30400
#define MIN_FUEL_RAW 4900

#define MAX_RPM_RAW 30400
#define MIN_RPM_RAW 4900

#define MAX_RPM_SPEEDOMETER 1000.f
#define MIN_RPM_SPEEDOMETER 0.f

#define MAX_RPM_TACHOMETER 1500.f
#define MIN_RPM_TACHOMETER 0.f

#define SPEEDOMETER_CHANNEL 1
#define TACHOMETER_CHANNEL 2
#define FUEL_CHANNEL 3

class NativeSampleModule : public NativeSampleModuleCxxSpec<NativeSampleModule> {
 public:
  NativeSampleModule(std::shared_ptr<CallInvoker> jsInvoker);

  std::string reverseString(jsi::Runtime& rt, std::string input);
  void storeAndCallJSCallback(jsi::Runtime& rt, jsi::Function jsCallback);
  void getVehicleData(jsi::Runtime &rt, AsyncCallback<std::string> callback);
  void install(jsi::Runtime& rt);
};

} // namespace facebook::react