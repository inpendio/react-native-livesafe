//
//  TipSubmitManager.h
//  LiveSafe
//
//  Created by Demetris Christou on 6/14/16.
//  Copyright © 2016 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TipSubmitDelegate.h"
#import "TipSubmitTask.h"

@class LSTip;

@interface TipSubmitManager : NSObject

+ (TipSubmitManager * _Nonnull)getInstance;

@property (nonatomic, strong, nonnull) NSMutableArray<TipSubmitTask *> *tipSubmitTasks;

// TODO: The retryStrategy parameter is of type RetryStrategy.
// But the compiler doesn't seem to allow the swift enum to be used
// in objc header file.
- (bool)startTipSubmitTask:(LSTip * _Nonnull)eventReport
         completionHandler:(void (^ _Nullable)(LSTip * _Nullable tip))completionHandler
           notifyOnFailure:(bool)shouldNotify
                  delegate:(id <TipSubmitDelegate> _Nullable)observer
                     retry:(NSInteger)retryStrategy;

- (void)stopTipSubmitRetryTasks;

- (void)cancelTipSubmit:(LSTip * _Nonnull)eventReport;

@end
