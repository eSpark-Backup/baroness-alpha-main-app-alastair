#include "react-native-bikegadget-mainapp.h"
#include <jsi/jsi.h>
#include <jsi/jsilib.h>
#include <thread>
#include <android/log.h>
#include <ReactCommon/CallInvoker.h>

using namespace facebook::jsi;
using namespace std;

namespace bikegadgetmainapp
{
	// Function to register helloWorld in JSI
	void registerHelloWorld(Runtime &jsiRuntime)
	{
		auto helloWorld = Function::createFromHostFunction(
			jsiRuntime,
			PropNameID::forAscii(jsiRuntime, "helloWorld"),
			0,
			[](Runtime &runtime,
			   const Value &thisValue,
			   const Value *arguments,
			   size_t count) -> Value
			{
				string helloworld = "helloworld Ash 123";
				return Value(runtime, String::createFromUtf8(runtime, helloworld));
			});

		jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", std::move(helloWorld));
	}

	void registerFoo(Runtime &jsiRuntime)
	{
		auto foo = Function::createFromHostFunction(
			jsiRuntime,
			PropNameID::forAscii(jsiRuntime, "foo"),
			1,
			[](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value
			{
				if (count < 1 || !arguments[0].isObject() || !arguments[0].getObject(runtime).isFunction(runtime))
				{
					throw JSError(runtime, "Expected a function as the first argument");
				}

				// Create a shared reference to the user callback
				auto userCallbackRef = std::make_shared<Object>(arguments[0].getObject(runtime));

				// Lambda to be run in the new thread
				auto f = [&runtime, userCallbackRef]()
				{
					auto val = std::make_shared<std::string>("hello world");
					auto error = std::make_shared<Value>(Value::undefined());

					// Periodically log messages to Android log and sleep for 5 seconds
					while (true)
					{
						__android_log_print(ANDROID_LOG_INFO, "MyApp", "Log message to Android");
                        userCallbackRef->asFunction(runtime).call(runtime, *error, *val);
						std::this_thread::sleep_for(std::chrono::seconds(5));
					}
				};

				// // Launch the lambda in a new thread
				std::thread thread_object(f);
				thread_object.detach();

				return Value::undefined();
			});

		jsiRuntime.global().setProperty(jsiRuntime, "foo", std::move(foo));
	}
	// Function to install the JSI bindings
	void install(Runtime &jsiRuntime)
	{
		// Register the helloWorld function
		registerHelloWorld(jsiRuntime);
		registerFoo(jsiRuntime);
	}

	double multiply(double a, double b)
	{
		return a * b;
	}
}
 