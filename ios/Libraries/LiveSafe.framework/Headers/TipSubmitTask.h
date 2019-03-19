//
//  TipSubmitTask.h
//  LiveSafeAppProd
//
//  Created by Demetris Christou on 10/22/15.
//  Copyright © 2015 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TipSubmitDelegate.h"

@class LSTip;

@interface TipSubmitTask : NSObject <TipSubmitDelegate>

@property (nonatomic, strong, nonnull) LSTip *currentEventReport;

// TODO: The retryStrategy parameter is of type RetryStrategy.
// But the compiler doesn't seem to allow the swift enum to be used
// in objc header file.
- (void)timeRetryTipSubmit:(LSTip * _Nonnull)eventReport
         completionHandler:(void (^ _Nullable)(void))completionHandler
           notifyOnFailure:(bool)shouldNotify
                  delegate:(id <TipSubmitDelegate> _Nullable)observer
                     retry:(NSInteger)retryStrategy;

- (void)setRetryStrategy:(NSInteger)newStrategy shouldNotify:(BOOL)raiseNotification;
- (void)setDelegate:(id <TipSubmitDelegate> _Nullable)newDelegate;
- (void)cancel;

@end
