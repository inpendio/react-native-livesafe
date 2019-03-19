#import "RNLivesafe.h"

@implementation ObjCall

@end

@implementation ObjMessage

@end

@implementation RNLivesafe

RCT_EXPORT_MODULE()

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

RCT_EXPORT_METHOD(init:(NSString *)clientKey secretKey:(NSString *)secretKey)
{
    // Init LS Manager
    [LSManager initializeWithAccessKey:clientKey
                             secretKey:secretKey
                    navigationBarStyle:nil];
    // Create User Session
    // TODO: update users fcm token
    [LSManager createSessionWithToken:nil
                       organizationId:nil
                           completion:^(LSError *error) {
                               if (error != nil)
                               {
                                   NSLog(@"LiveSafe SDK init failed");
                               }
                           }];
}

// Updates User Token
RCT_EXPORT_METHOD(updateDeviceToken: (NSData* ) token)
{
    [LSManager updateDeviceToken: token];
}


// Opens LiveSafe's UI to submit new Tip. type param most be one of the TipTypes LiveSafe Provides. (getTipTypes)
RCT_EXPORT_METHOD(submitTip: (NSDictionary* ) type){
    LSTipType *tipType = [[LSTipType alloc] initWithTypeId: (int)[type objectForKey:@"name"]];
    LSReportTipConfig *reportTipConfig = [[LSReportTipConfig alloc] initWithTipType:tipType];
    
    // Saving ummutable copy of Initial VC
    UIViewController *const MainViewController =  [UIApplication sharedApplication].delegate.window.rootViewController;
    
    // Getting LiveSafe NC
    UINavigationController* lsNav = [LSTipSubmitManager
                                     startReportTip: reportTipConfig
                                     completion:^(LSTip *tip, LSError *error) {
                                         // When this is called the LiveSafe SDK submitted the SDK.
                                         if (error == nil)
                                         {
                                         }
                                         else
                                         {
                                             
                                             NSLog(@"Error reporting tip");
                                         }
                                         // Going back to Initial VC once tip is succesfully reported
                                         [UIApplication sharedApplication].delegate.window.rootViewController = MainViewController;
                                     }];
    
    // Forcing LiveSafe's UC in root
    [UIApplication sharedApplication].delegate.window.rootViewController = lsNav;
    
}

// Util function to transfrom LSTipType to NSDictionary
-(NSDictionary*)normalizeTipType:(LSTipType*)tip{
    NSDictionary* tipNormalized =  @{
                                     @"value": @(tip.tipTypeId),
                                     @"name": tip.displayName,
                                     @"icon": tip.imageName,
                                     @"mapIcon": tip.mapImageName,
                                     @"hintText": tip.hintText,
                                     @"chatText": tip.chatText};
    return tipNormalized;
}

// Returns a promise with the array of TipTypes objects defined above
RCT_REMAP_METHOD(getTipTypes,
                 getTipTypesWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    [LSTipSubmitManager
     getTipTypes:^(NSArray<LSTipType *> *tipTypes, LSError *error) {
         if (tipTypes)
         {
             NSMutableArray* tipsNormalized = [NSMutableArray array];
             for (LSTipType* tip in tipTypes) {
                 [tipsNormalized addObject: [self normalizeTipType:tip]];
             }
             
             resolve(tipsNormalized);
         }
         else
         {
             reject(@"Error @getTypes", @"couldn't retrieve type types", (NSError* ) error);
         }
     }];
}

// Util function to transfrom LSTip to NSDictionary
-(NSDictionary*)normalizeTip:(LSTip*)tip{
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"d MM yyyy"];
    NSDictionary* tipNormalized =  @{
                                     @"text": tip.text,
                                     @"isAnonymous": tip.isAnonymous ? @YES : @NO,
                                     @"dateCreated": [formatter stringFromDate:tip.dateCreated],
                                     @"longitude": @(tip.location.coordinate.longitude),
                                     @"latitude": @(tip.location.coordinate.latitude),
                                     @"tipType": tip.tipType.displayName,
                                     @"uuid": tip.uuid
                                     };
    return tipNormalized;
}

// Gets User's tip history and returns a promise with array of Tip objects
RCT_REMAP_METHOD(getTipHistory,
                 getTipHistoryWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    [LSTipSubmitManager getSubmittedTips:^(NSArray<LSTip *> * Tips, LSError * Error) {
        if (Tips)
        {
            NSMutableArray* tipsNormalized = [NSMutableArray array];
            for (LSTip* tip in Tips) {
                [tipsNormalized addObject: [self normalizeTip:tip]];
            }
            resolve(tipsNormalized);
        }
        else {
            reject(@"getSubmittedTypes error", @"Couldn't retrieve submitted types", (NSError* ) Error);
        }
    }];
}

// Checks if user is authenticated. If user is not, it will open UI to authenticate the user using phone number
RCT_EXPORT_METHOD(authentication){
    // Saving ummutable copy of Initial VC
    UIViewController *const MainViewController =  [UIApplication sharedApplication].delegate.window.rootViewController;
    
    if ([LSManager isAuthorized]) {
        NSLog(@"User is already authorized");
    }
    else {
        UINavigationController* lsNav = [LSManager authorizeIfNeededWithCompletion:^(LSError * error) {
            if (error == nil) {
                NSLog(@"ERROR is nill");
            }
            else {
                NSLog(@"ERROR:is not NILL %@",
                      error.description);
            }
            
            // Going back to Initial VC once tip is succesfully reported
            [UIApplication sharedApplication].delegate.window.rootViewController = MainViewController;
        }
                                         ];
        
        // Forcing LiveSafe's UC in root
        [UIApplication sharedApplication].delegate.window.rootViewController = lsNav;
    }
}

// Returns boolean indicating if user is logged in
RCT_REMAP_METHOD(isLoggedIn,
                 isLoggedInWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    if([LSManager isAuthorized]){
        resolve(@YES);
    }else{
        resolve(@NO);
        //reject(@"User not logged In", @"User not logged In", nil);
    }
}

// Updates userLocation
RCT_EXPORT_METHOD(updateUserLocation: (double) latitude :(double) longitude){
    CLLocation *location = [[CLLocation alloc] initWithLatitude:latitude longitude: longitude];
    [LSManager
     updateUserLocation: location
     completion:^(LSError *error) {
         if (error != nil)
         {
             NSLog(@"failed to update users location");
         }
     }];
}

// Calls organization security using number param
// This function only works on physical devices
RCT_EXPORT_METHOD(callOrganizationSecurity: (NSString* ) number :(double) latitude :(double) longitude){
    CLLocation *location = [[CLLocation alloc] initWithLatitude:latitude longitude: longitude];
    //ObjCall is a custom Call Object that follows the LiveSafe's EmergencyCall Protocol
    ObjCall *callItem = [[ObjCall alloc] init];
    callItem.phoneNumber = number;
    callItem.location = location;
    callItem.sendEvent = true;
    callItem.enableLocationTracking = true;
    callItem.tipTypeId = [TipTypeConstants kTipTypeIdCallOrganizationSecurity];
    
    [LSEmergencyOptionsManager makeCallWithCallItem:callItem completion:^(LSTip *tip, LSError *error) {
        if (error != nil) {
            NSLog(@"ERROR: Failed to make emergency call, error is [%@]", error.description);
        }
        if (tip == nil) {
            NSLog(@"ERROR: Failed to send tip for emergency call");
        }
    }];
}

// Gets and calls local emergency number
// This function only works on physical devices
RCT_EXPORT_METHOD(callLocalEmergencyService: (double) latitude :(double) longitude){
    CLLocation *location = [[CLLocation alloc] initWithLatitude:latitude longitude: longitude];
    [LSEmergencyOptionsManager getLocalEmergencyPhoneWithLocation:location
       completion:^(NSString *phoneNumber) {
           //ObjCall is a custom Call Object that follows the LiveSafe's EmergencyCall Protocol
           ObjCall *callItem = [[ObjCall alloc] init];
           callItem.phoneNumber = phoneNumber;
           callItem.location = location;
           callItem.sendEvent = YES;
           callItem.enableLocationTracking = YES;
           callItem.tipTypeId = [TipTypeConstants kTipTypeIdCallOrganizationSecurity];
           
           [LSEmergencyOptionsManager makeCallWithCallItem:callItem completion:^(LSTip *tip, LSError *error) {
               if (error != nil) {
                   NSLog(@"ERROR: Failed to make emergency call, error is [%@]", error.description);
               }
               
               if (tip == nil) {
                   NSLog(@"ERROR: Failed to send tip for emergency call");
               }
               
           }];
       }];

}

// Opens UI that sends Emergency message to organization security
RCT_EXPORT_METHOD(messageOrganizationSecurity){
    
    UIViewController *const MainViewController =  [UIApplication sharedApplication].delegate.window.rootViewController;
    
    ObjMessage *msgItem = [[ObjMessage alloc] init];
    msgItem.title = @"Message Organization Security";
    UINavigationController* lsNav = [LSEmergencyOptionsManager sendMessageWithMessageItem:msgItem
        completion:^(LSTip *tip, LSError *error) {
           if (tip != nil) {
               NSLog(@"Successfully submitted message");
           } else {
               NSLog(@"ERROR: Failed to send message, error is [%@]", error.description);
           }
        
            // Going back to Initial VC once tip is succesfully reported
            [UIApplication sharedApplication].delegate.window.rootViewController = MainViewController;
        }];
    
    [UIApplication sharedApplication].delegate.window.rootViewController = lsNav;
}

@end


/**
 
 NEED DOCS
 
 RCT_EXPORT_METHOD(showMap){
 config.googlePlacesKey = "YOUR_GOOGLE_PLACES_KEY"
 LSMapManager.initializeLivesafeMapWithLayers(withGoogleMapsKey: "AIzaSyA8NnyGPDj-TBi3hR_h_7y1AfhFvqoJQ3Y")
 
 }**/
