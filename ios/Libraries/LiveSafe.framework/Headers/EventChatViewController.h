//
//  EventChatViewController.h
//  LiveSafeAppProd
//
//  Created by Demetris Christou on 11/13/14.
//  Copyright (c) 2014 LiveSafe. All rights reserved.
//

#import "ChatViewController.h"
#import "LSCommonViewController.h"
#import <UIKit/UIKit.h>

@class TipChatContext;

@interface EventChatViewController: LSCommonViewController

@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (strong, nonatomic)
  IBOutlet UIActivityIndicatorView *activityIndicator;

// Location tracking view and children.
@property (strong, nonatomic) IBOutlet UIView *locationTrackingView;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *locationTrackingViewHeight;
@property (strong, nonatomic) IBOutlet UIView *hSpacer1;
@property (strong, nonatomic) IBOutlet UIView *hSpacer2;
@property (strong, nonatomic) IBOutlet UIImageView *stopLocationTrackingImageView;
@property (strong, nonatomic) IBOutlet UIButton *stopLocationTrackingButton;

@property (nonatomic, strong) TipChatContext *tipChatContext;
@property (nonatomic, strong) ChatViewController *chatViewController;

- (IBAction)stopLocationTrackingAction:(id)sender;

- (void)cleanup;
// NOTE: This can eventually be removed
- (void)executeBackButton:(id)sender;

@end
