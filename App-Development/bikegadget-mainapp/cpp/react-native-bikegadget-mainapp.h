#ifndef BIKEGADGETMAINAPP_H
#define BIKEGADGETMAINAPP_H

#include <jni.h>

namespace facebook {
namespace jsi {
class Runtime;
}
}

namespace bikegadgetmainapp {
  double multiply(double a, double b);
  void install(facebook::jsi::Runtime &jsiRuntime);
  void registerHelloWorld(facebook::jsi::Runtime &jsiRuntime);
}

#endif /* BIKEGADGETMAINAPP_H */
