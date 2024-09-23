#include "NativeSampleModule.h"
#include <thread>

namespace facebook::react {

NativeSampleModule::NativeSampleModule(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeSampleModuleCxxSpec(std::move(jsInvoker)) {}

std::string NativeSampleModule::reverseString(jsi::Runtime& rt, std::string input) {
  return std::string(input.rbegin(), input.rend());
}

void NativeSampleModule::storeAndCallJSCallback(jsi::Runtime& rt, jsi::Function jsCallback) {

    auto createMessage = [](int counter) {
        return "Hello " + std::to_string(counter);
    };

    std::thread([callback = std::make_shared<jsi::Function>(std::move(jsCallback)), this, createMessage]() mutable 
    {
        int counter = 0;

        while (true) 
        {
            std::string message = createMessage(counter++);

            auto messagePtr = std::make_shared<std::string>(std::move(message));

            jsInvoker_->invokeAsync([callback, messagePtr, this](jsi::Runtime& rt) 
            {
                auto jsString = jsi::String::createFromUtf8(rt, *messagePtr);
                callback->call(rt, jsString); 
            });

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }).detach(); 
}

void NativeSampleModule::callback(jsi::Runtime &rt, AsyncCallback<std::string> callback) {
    std::thread t([callback = std::move(callback)]() {
        int counter = 0;
        while (1)
        {
            /* code */
            callback.call("works without any issues " + std::to_string(counter++));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
    });
    t.detach();
}


void NativeSampleModule::install(jsi::Runtime &jsiRuntime) {

    auto helloWorld = jsi::Function::createFromHostFunction(jsiRuntime,
                                                       jsi::PropNameID::forAscii(jsiRuntime,
                                                                            "helloWorld"),
                                                       0,
                                                       [](jsi::Runtime &runtime,
                                                          const jsi::Value &thisValue,
                                                          const jsi::Value *arguments,
                                                          size_t count) -> jsi::Value {
        std::string helloworld = "helloworld";


        return jsi::Value(runtime,
                     jsi::String::createFromUtf8(
                                            runtime,
                                            helloworld));

    });

    jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", std::move(helloWorld));

    auto multiply = jsi::Function::createFromHostFunction(jsiRuntime,
                                                     jsi::PropNameID::forAscii(jsiRuntime,
                                                                          "multiply"),
                                                     2,
                                                     [](jsi::Runtime &runtime,
                                                        const jsi::Value &thisValue,
                                                        const jsi::Value *arguments,
                                                        size_t count) -> jsi::Value {
        int x = arguments[0].getNumber();
        int y = arguments[1].getNumber();

        return jsi::Value(x * y);

    });

    jsiRuntime.global().setProperty(jsiRuntime, "multiply", std::move(multiply));

    auto multiplyWithCallback = jsi::Function::createFromHostFunction(jsiRuntime,
                                                                 jsi::PropNameID::forAscii(jsiRuntime,
                                                                                      "multiplyWithCallback"),
                                                                 3,
                                                                 [](jsi::Runtime &runtime,
                                                                    const jsi::Value &thisValue,
                                                                    const jsi::Value *arguments,
                                                                    size_t count) -> jsi::Value {
        int x = arguments[0].getNumber();
        int y = arguments[1].getNumber();

        arguments[2].getObject(runtime).getFunction(runtime).call(runtime, x * y);

        return jsi::Value();

    });

    jsiRuntime.global().setProperty(jsiRuntime, "multiplyWithCallback", std::move(multiplyWithCallback));

    auto callFromCplusplus = jsi::Function::createFromHostFunction(
        jsiRuntime,
        jsi::PropNameID::forAscii(jsiRuntime, "callFromCplusplus"),
        1,
        [this](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments, size_t count) -> jsi::Value {

            // Store the callback function reference
            auto userCallbackRef = std::make_shared<jsi::Object>(arguments[0].getObject(runtime));

            // Helper function to create "Hello {counter}" string
            auto createMessage = [&runtime](int counter) {
                return jsi::String::createFromUtf8(runtime, "Hello " + std::to_string(counter));
            };


            std::thread([userCallbackRef, this, &runtime, createMessage]() mutable {
                int counter = 0;  // Initialize counter

                while (true) {
                    // Prepare values
                    auto valPtr = std::make_shared<jsi::String>(createMessage(counter++));
                    auto errorPtr = std::make_shared<jsi::Value>(jsi::Value::undefined());

                    // Async call to JS function
                    jsInvoker_->invokeAsync([userCallbackRef, valPtr, errorPtr, &runtime]() {
                        userCallbackRef->asFunction(runtime).call(runtime, *errorPtr, *valPtr);
                    });

                    // Sleep for 5 seconds
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }).detach();  // Detach the thread to run independently

            return jsi::Value::undefined();
        }
    );
    jsiRuntime.global().setProperty(jsiRuntime, "callFromCplusplus", std::move(callFromCplusplus));
}


} // namespace facebook::react