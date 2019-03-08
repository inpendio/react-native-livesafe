import { NativeEventEmitter, NativeModules } from "react-native";
const { RNLivesafe } = NativeModules;

class RNLiveSafe extends NativeEventEmitter {
  constructor(nativeModule) {
    super(nativeModule);
    this.init = nativeModule.init;
    this.showMap = nativeModule.showMap;
    this.getTips = nativeModule.getTips;
    this.submitTip = nativeModule.submitTip;
    this.authentification = nativeModule.authentification;
    this.updateUserLocation = nativeModule.updateUserLocation;
    this.emergencyOptions = nativeModule.emergencyOptions;
    this.messageOrganzationSecurity = nativeModule.messageOrganzationSecurity;
    this.callLocalEmergencyService = nativeModule.callLocalEmergencyService;
    this.callOrganizationSecurity = nativeModule.callOrganizationSecurity;
  }
}

export default new RNLiveSafe(RNLivesafe);
