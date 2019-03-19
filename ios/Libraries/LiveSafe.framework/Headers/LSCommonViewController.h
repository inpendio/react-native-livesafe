//
//  LSCommonViewController.h
//  LiveSafeAppProd
//
//  Created by Demetris Christou on 7/29/14.
//  Copyright (c) 2014 LiveSafe. All rights reserved.
//

#import "LiveSafeViewController.h"
#import <UIKit/UIKit.h>

@interface LSCommonViewController : LiveSafeViewController

@property CGFloat keyboardHeight, keyboardDeltaHeight;

- (void)addActivityIndicatorToView:(UIView *)parentView;
- (void)removeActivityIndicator;
- (NSTimeInterval)keyboardAnimationDurationForNotification:
  (NSNotification *)notification;
- (CGRect)keyboardFrameForNotification:(NSNotification *)notification;

@end
