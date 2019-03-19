//
//  TipSubmitDelegate.h
//  LiveSafeAppProd
//
//  Created by Demetris Christou on 10/19/15.
//  Copyright Â© 2015 LiveSafe. All rights reserved.
//

#import "TipSubmitConstants.h"
#import <Foundation/Foundation.h>

@class LSTip;
@class LSMediaItem;

@protocol TipSubmitDelegate <NSObject>

@optional

- (void)eventReport:(LSTip *)tip
         submitStep:(TipSubmitStepType)step
      statusUpdated:(TipSubmitStatusType)newStatus
     additionalInfo:(NSDictionary *)submitInfo;

- (void)eventMedia:(LSMediaItem *)mediaItem
        submitStep:(TipSubmitStepType)step
     statusUpdated:(TipSubmitStatusType)newStatus
    additionalInfo:(NSDictionary *)submitInfo;

@end