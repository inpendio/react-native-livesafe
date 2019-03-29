import { NativeEventEmitter, NativeModules } from "react-native";
const { RNLivesafe } = NativeModules;

class RNLiveSafe extends NativeEventEmitter {
  constructor(nativeModule) {
    super(nativeModule);
    this.init = nativeModule.init; // ios & android
    this.showMap = nativeModule.showMap; //android?  theres no ios documentation for this?
    this.getTipTypes = nativeModule.getTipTypes;// ios & android
    this.getTipHistory = nativeModule.getTipHistory;// ios & android
    this.submitTip = nativeModule.submitTip;// ios & android
    this.authentication = nativeModule.authentication;// ios & android
    this.isLoggedIn = nativeModule.isLoggedIn;// ios (dont know if we need this, was following the readme)
    this.updateUserLocation = nativeModule.updateUserLocation; //android & ios
    this.updateDeviceToken = nativeModule.updateDeviceToken //ios
    this.registerForNotifications = nativeModule.registerForNotifications //ios
    this.emergencyOptions = nativeModule.emergencyOptions; //android & ios
    this.messageOrganizationSecurity = nativeModule.messageOrganizationSecurity; //android
    this.callLocalEmergencyService = nativeModule.callLocalEmergencyService; //android & ios
    this.callOrganizationSecurity = nativeModule.callOrganizationSecurity; //android & ios
    this.showTipHistory = nativeModule.showTipHistory; // ios
    this.switchOrganization = nativeModule.switchOrganization; // ios & android
  }
}

export default new RNLiveSafe(RNLivesafe);
