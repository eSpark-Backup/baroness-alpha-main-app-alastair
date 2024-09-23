import { TurboModule, TurboModuleRegistry } from "react-native";

export interface Spec extends TurboModule {
  readonly reverseString: (input: string) => string;
  readonly storeAndCallJSCallback: (callback: (result: string) => void) => void;
  readonly callback: (callback: (result: string) => void) => void;
  readonly install: () => void;
  
}

//@ts-ignore
const RegisteredMethods_t: {
  readonly callFromCplusplus: (callback: (error: string | undefined, result: string) => void) => void;
  //@ts-ignore
} = global;

export const RegisteredMethods = RegisteredMethods_t;

export default TurboModuleRegistry.getEnforcing<Spec>("NativeSampleModule");