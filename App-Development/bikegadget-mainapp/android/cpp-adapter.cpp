#include <jni.h>
#include "react-native-bikegadget-mainapp.h"
#include <jsi/jsi.h>
#include <jsi/jsilib.h>

extern "C" JNIEXPORT jdouble JNICALL
Java_com_bikegadgetmainapp_BikegadgetMainappModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b)
{
    return bikegadgetmainapp::multiply(a, b);
}

extern "C" JNIEXPORT void JNICALL
Java_com_bikegadgetmainapp_BikegadgetMainappModule_nativeInstall(JNIEnv *env, jclass type, jlong jsi)
{
    auto runtime = reinterpret_cast<facebook::jsi::Runtime *>(jsi);
    bikegadgetmainapp::install(*runtime);
}