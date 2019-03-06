import { NativeEventEmitter, NativeModules } from "react-native";
const { RNLivesafe } = NativeModules;

console.log(NativeModules);

class RNLiveSafe extends NativeEventEmitter {
  constructor(nativeModule) {
    super(nativeModule);
    this.init = nativeModule.init;
  }
}

export default new RNLiveSafe(RNLivesafe);
