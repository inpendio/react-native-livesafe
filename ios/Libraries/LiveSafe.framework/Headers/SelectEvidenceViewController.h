//
//  SelectEvidenceViewController.h
//  LiveSafeMobileApp
//
//  Created by Demetris Christou on 4/23/13.
//  Copyright (c) 2013 LiveSafe. All rights reserved.
//

#import "LSCommonViewController.h"
#import "TipSubmitDelegate.h"
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@class LSTip;
@class TipSubmitContext;
@class LSMediaItem;
@class LSReportTipConfig;
@class LSError;

@interface SelectEvidenceViewController
    : LSCommonViewController <
          UINavigationControllerDelegate, UIImagePickerControllerDelegate,
          UITextViewDelegate, AVAudioRecorderDelegate,
          TipSubmitDelegate, UIAlertViewDelegate>

extern NSString * _Nonnull const ADD_EVENT_RESPONSE_JSON_KEY;
extern NSString * _Nonnull const TIP_CONFIRMATION_MESSAGE_KEY;

@property(strong, nonatomic, nonnull) IBOutlet UIView *containerView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *headerView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *bodyView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *footerView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *spacerOne;
@property(strong, nonatomic, nonnull) IBOutlet UIView *spacerTwo;
@property(strong, nonatomic, nonnull) IBOutlet UIView *spacerThree;
@property(strong, nonatomic, nonnull) IBOutlet UIView *spacerFour;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *incidentTypeLabel;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *buttonRecordAudio;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *buttonTakePicture;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *buttonTakeVideo;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *selectEvidenceViewTitle;
@property(strong, nonatomic, nonnull) IBOutlet UITextView *testimonyTextView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *textViewWrapperView;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *sendAnonymousLabel;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *addressLabel;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *sentByLabel;
@property(strong, nonatomic, nonnull) IBOutlet UISwitch *sendAnonymouslySwitch;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *buttonSendReport;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *locationTrackingLabel;

@property(strong, nonatomic, nonnull) IBOutlet UIButton *viewAttachedPhotoButton;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *attachedPhotoNumberLabel;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *viewAttachedVideoButton;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *attachedVideoNumberLabel;
@property(strong, nonatomic, nonnull) IBOutlet UIButton *viewAttachedAudioButton;
@property(strong, nonatomic, nonnull) IBOutlet UILabel *attachedAudioNumberLabel;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *photoAttachedWidthConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *videoAttachedWidthConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *audioAttachedWidthConstraint;
@property(strong, nonatomic, nonnull) IBOutlet UIView *attachedPhotoView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *attachedVideoView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *attachedAudioView;
@property(strong, nonatomic, nonnull) IBOutlet UIView *tipDetailsContentView;

@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *sendReportButtonBottomConstraint;

@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *underLocationTrackingSpaceConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *footerViewProportionalHeightConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *containerViewTopConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *containerViewBottomConstraint;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *sendAnonymousViewHeightConstraint;
@property(strong, nonatomic, nonnull) IBOutlet NSLayoutConstraint
    *contentViewBottomOffset;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *contentViewTopOffset;
@property(strong, nonatomic, nonnull)
    IBOutlet NSLayoutConstraint *headerViewBottomBodyViewTopConstraint;

@property(nonatomic, strong, nonnull) TipSubmitContext *tipSubmitContext;

@property(nonatomic) bool userConfirmedExit;

- (IBAction)anonymousSwitchFlipped:(id _Nullable)sender;
- (IBAction)actionTakePicture:(id _Nullable)sender;
- (IBAction)actionTakeVideo:(id _Nullable)sender;
- (IBAction)actionAddAudio:(id _Nullable)sender;
- (IBAction)actionSubmitTip:(id _Nullable)sender;

- (bool)isUserInputValid;

- (IBAction)viewAttachedPhoto:(id _Nullable)sender;

- (IBAction)viewAttachedAudio:(id _Nullable)sender;

- (IBAction)viewAttachedVideo:(id _Nullable)sender;

// NOTE: This is only here until more of this class migrates to swift. Trying to
// keep all of our iVars private
- (void)executeBackButton:(id _Nullable)sender;

- (void)updateViewForLocation:(CLLocation * _Nullable)location;

@end
