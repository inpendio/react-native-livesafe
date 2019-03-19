//
//  ChatViewController.h
//  LiveSafeMobileApp
//
//  Created by kiwitech on 18/07/13.
//  Copyright (c) 2013 LiveSafe. All rights reserved.
//

#import "LSCommonViewController.h"
#import "TipDetailsChatViewCellDelegate.h"
#import "TipSubmitController.h"
#import "TipSubmitDelegate.h"
#import <UIKit/UIKit.h>

@class LSChat;
@class LSTip;
@class LiveSafeAPIManager;

@interface ChatViewController
  : LSCommonViewController <TipDetailsChatViewCellDelegate, TipSubmitDelegate,
                            UIAlertViewDelegate, UITableViewDelegate,
                            UITableViewDataSource>

@property (nonatomic, strong) LSTip *tip;
@property (strong, nonatomic) NSMutableArray<LSChat *> *eventChatArray;

@property (strong, nonatomic) IBOutlet UITableView *chatTableView;
@property (strong, nonatomic) IBOutlet UIButton *buttonSend;
@property (nonatomic, strong) IBOutlet UITextView *composeMessageTextView;
@property (strong, nonatomic) IBOutlet UIView *bottomBarView;

@property (strong, nonatomic) IBOutlet NSLayoutConstraint *composeViewHeight;
@property (strong, nonatomic)
  IBOutlet NSLayoutConstraint *composeViewBottomConstraint;
@property (strong, nonatomic)
  IBOutlet NSLayoutConstraint *chatEntryBottomConstant;
@property (strong, nonatomic)
  IBOutlet NSLayoutConstraint *sendButtonBottomConstant;

// Note: set as a weak reference to avoid a retain cycle.
@property (nonatomic, weak) UIView *containerView;

@property (nonatomic) bool showKeyboardOnLoad;
@property (nonatomic) bool isHidingQuickTypeKeyboard;
@property (nonatomic) bool isSendChatDisabled;

@property (strong, nonatomic) LiveSafeAPIManager *apiManager;

- (IBAction)sendButtonClicked:(id)sender;

- (id)initWithContainerView:(UIView *)parentView;
- (void)addChatResponse:(LSChat *)chatResponse;
- (void)initChat;
- (bool)isLoadChatHistoryInProgress;
- (void)dismissKeyboard;
- (void)sendChatMessage:(NSString *)chatMessage;

- (void)cleanup;

@end
