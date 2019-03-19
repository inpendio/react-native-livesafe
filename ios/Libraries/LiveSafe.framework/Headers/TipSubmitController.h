//
//  TipSubmitController.h
//  LiveSafeAppProd
//
//  Created by Shayan on 10/15/15.
//  Copyright © 2015 LiveSafe. All rights reserved.
//

#import "TipSubmitDelegate.h"
#import <Foundation/Foundation.h>

// Note: The Apple documentation states that to importing swift classes
// in .h files should be done using forward class declaration.
// https://developer.apple.com/library/ios/documentation/Swift/Conceptual/BuildingCocoaApps/MixandMatch.html
@class LSTip;

@interface TipSubmitController : NSObject

@property (nonatomic, strong) LSTip *incidentReport;
@property (nonatomic, weak) id<TipSubmitDelegate> tipSubmitDelegate;
@property (nonatomic) bool raiseNotificationOnFailure;

- (void)startTipSubmit:(LSTip *)eventReport
              callback:(id)delegate
      sendNotification:(bool)shouldNotifyOnFailure;
- (void)cancelTip;

@end
