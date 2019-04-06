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

RCT_REMAP_METHOD(init, :(NSString *)clientKey
                 secretKey:(NSString *)secretKey
                 initWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject
                )
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
                                   reject(@"init error", @"Could not init", (NSError* ) error);
                                   NSLog(@"LiveSafe SDK init failed");
                               } else
                               {
                                   resolve(@YES);
                                   [[UIApplication sharedApplication] registerForRemoteNotifications];
                               }
                           }];
}

// Updates User Token
RCT_EXPORT_METHOD(updateDeviceToken: (NSData* ) token)
{
    [LSManager updateDeviceToken: token];
}


RCT_EXPORT_METHOD(registerForNotifications){
    [LSManager registerNotificationSettings];
}

// Opens LiveSafe's UI to submit new Tip. type param most be one of the TipTypes LiveSafe Provides. (getTipTypes)
RCT_EXPORT_METHOD(submitTip: (NSDictionary* ) type){
    LSTipType *tipType = [[LSTipType alloc] initWithTypeId: [[type objectForKey:@"value"] intValue]];
    LSReportTipConfig *reportTipConfig = [[LSReportTipConfig alloc] initWithTipType:tipType];
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];

    UINavigationController* startTipNC = [LSTipSubmitManager
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

                                          [(UINavigationController*) delegate.rootViewController dismissViewControllerAnimated:YES completion:nil];
                                      }];

    ((UINavigationController*) delegate.rootViewController).navigationBarHidden = NO;
    [(UINavigationController*)delegate.rootViewController pushViewController: startTipNC.childViewControllers[0] animated:YES];

}

RCT_EXPORT_METHOD(startChatForTip: (NSDictionary*) tipDictionary){
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    LSTip * tip = [self DictionaryToLSTip:tipDictionary];

    UINavigationController* chatNC = [LSChatManager startChatForTip:tip error:nil];

    ((UINavigationController*) delegate.rootViewController).navigationBarHidden = NO;
    [(UINavigationController*)delegate.rootViewController pushViewController: chatNC.childViewControllers[0] animated:YES];

}


// Util function to transform LSTipType to NSDictionary
-(NSDictionary*)LSTipTypeToDictionary:(LSTipType*)tip{
    NSDictionary* tipNormalized =  @{
                                     @"value": @(tip.tipTypeId),
                                     @"name": tip.displayName,
                                     @"icon": tip.imageName,
                                     @"mapIcon": tip.mapImageName,
                                     @"hintText": tip.hintText,
                                     @"chatText": tip.chatText};
    return tipNormalized;
}

// Util function to transfrom LSTip to NSDictionary
-(NSDictionary*)LSTipToDictionary:(LSTip*)tip{
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

// Util function to transfrom LSTip to NSDictionary
-(LSTip*)DictionaryToLSTip:(NSDictionary*)tip{
    LSTip* tipReturn = [LSTip retrieveStoredTip:tip[@"uuid"] error:nil];
    return tipReturn;
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
                 [tipsNormalized addObject: [self LSTipTypeToDictionary:tip]];
             }

             resolve(tipsNormalized);
         }
         else
         {
             reject(@"Error @getTypes", @"couldn't retrieve type types", (NSError* ) error);
         }
     }];
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
                [tipsNormalized addObject: [self LSTipToDictionary:tip]];
            }
            resolve(tipsNormalized);
        }
        else {
            reject(@"getSubmittedTypes error", @"Couldn't retrieve submitted types", (NSError* ) Error);
        }
    }];
}

RCT_EXPORT_METHOD(showTipHistory) {
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    ((UINavigationController*) delegate.rootViewController).navigationBarHidden = NO;
    [LSTipSubmitManager showUserActivityUsing:(UINavigationController*)delegate.rootViewController];
}

// Checks if user is authenticated. If user is not, it will open UI to authenticate the user using phone number
RCT_REMAP_METHOD(authentication,
                 authenticationWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject
                 )
{
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];

    if ([LSManager isAuthorized]) {
        NSLog(@"User is already authorized");
    }
    else {
        UINavigationController* lsNav = [LSManager authorizeIfNeededWithCompletion:^(LSError * error) {
            if (error == nil) {
                resolve(@YES);
            }
            else {
                resolve(@NO);
            }

            // Going back to Initial VC once tip is succesfully reported
            //((UINavigationController*) delegate.rootViewController).navigationBarHidden = YES;
            //[(UINavigationController*) delegate.rootViewController dismissViewControllerAnimated:YES completion:nil];
            [(UINavigationController*) delegate.rootViewController popToRootViewControllerAnimated:YES];
        }
                                         ];

        // Forcing LiveSafe's UC in root
        ((UINavigationController*) delegate.rootViewController).navigationBarHidden = NO;
        [(UINavigationController*)delegate.rootViewController pushViewController: lsNav.childViewControllers[0] animated:YES];
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
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    //UIViewController *const MainViewController =  [UIApplication sharedApplication].delegate.window.rootViewController;

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
            //((UINavigationController*) delegate.rootViewController).navigationBarHidden = YES;
            [(UINavigationController*) delegate.rootViewController dismissViewControllerAnimated:YES completion:nil];

        }];

    ((UINavigationController*) delegate.rootViewController).navigationBarHidden = NO;
    [(UINavigationController*)delegate.rootViewController pushViewController: lsNav.childViewControllers[0] animated:YES];
}

RCT_EXPORT_METHOD(endSession) {
    [LSManager endSession];
}

// Returns boolean indicating if user is logged in
RCT_REMAP_METHOD(getOrganization,
                 orgId:(NSInteger) orgId
                 getOrganizationWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    [LSManager getOrganizationDetails:orgId completion:^(LSOrganization *org, LSError *error) {
       if (error != nil)
       {
           //Incompatible block pointer types sending 'void (^)(LSError *__strong)' to parameter of type 'void (^ _Nonnull)(LSOrganization * _Nullable __strong, LSError * _Nullable __strong)'
           reject(@"getOrganization error", @"Could not get OrgID", (NSError* ) error);
       }
       else
       {
           resolve(org.name);
       }
    }];
}

RCT_REMAP_METHOD(setOrganization,
                 orgId: (NSInteger) orgId
                 sethOrganizationWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    [LSManager setOrganization: orgId completion:^(LSError *error) {
        if (error != nil)
        {
            reject(@"setOrganization error", @"Could not set OrgID", (NSError* ) error);
        }
        else
        {
            resolve(@YES);
        }
    }];
}


RCT_EXPORT_METHOD(stopActiveTracking) {
    [[LSLocationServices shared] stopActiveTracking];
}
@end
