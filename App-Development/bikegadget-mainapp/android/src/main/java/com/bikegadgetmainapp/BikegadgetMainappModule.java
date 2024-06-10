package com.bikegadgetmainapp;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.RuntimeExecutor;

@ReactModule(name = BikegadgetMainappModule.NAME)
public class BikegadgetMainappModule extends NativeBikegadgetMainappSpec {
  public static final String NAME = "BikegadgetMainapp";

  public BikegadgetMainappModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  static {
    System.loadLibrary("react-native-bikegadget-mainapp");
  }

  private static native double nativeMultiply(double a, double b);
  private static native void nativeInstall(long jsiPtr);

  // Example method
  // See https://reactnative.dev/docs/native-modules-android
  @Override
  public double multiply(double a, double b) {
    ReactApplicationContext context = getReactApplicationContext();
    return nativeMultiply(a, b);
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
      try {
          ReactApplicationContext context = getReactApplicationContext();
          // RuntimeExecutor runtimeExecutor = context.getRuntimeExecutor();
          nativeInstall(context.getJavaScriptContextHolder().get());
          return true;
      } catch (Exception e) {
          return false;
      }
  }
}
