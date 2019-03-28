#import <React/RCTViewManager.h>
#import <React/RCTBridgeDelegate.h>
#import <React/RCTBridgeModule.h>
#import <React/RCTBridge.h>
#import <React/RCTBundleURLProvider.h>
#import <React/RCTRootView.h>

#import <UIKit/UIKit.h>

#import <LiveSafe/LiveSafe.h>

#import "IMPORT_APP_DELEGATE_HERE";


@interface RNLivesafe : NSObject <RCTBridgeModule>
@end

@interface ObjCall : NSObject <EmergencyCall>

@property (assign) CLLocation *location;
@property (assign) BOOL sendEvent;
@property (assign) BOOL enableLocationTracking;
@property (assign) NSInteger * tipTypeId;
@property (nonatomic, strong) NSString * phoneNumber;
@property (nonatomic, strong) NSString * emergencyText;
@property (nonatomic, strong) NSString * title;

@end

@interface ObjMessage : NSObject <EmergencyMessage>

@property (nonatomic, strong) NSString * hintText;
@property (nonatomic, strong) NSString * emergencyText;
@property (nonatomic, strong) NSString * title;

@end
