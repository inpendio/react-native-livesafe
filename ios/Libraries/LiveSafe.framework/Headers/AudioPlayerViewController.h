//
//  AudioPlayerViewController.h
//  LiveSafeMobileApp
//
//  Created by Demetris Christou on 6/14/13.
//  Copyright (c) 2013 LiveSafe. All rights reserved.
//

#import "LSCommonViewController.h"
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@class AudioRecorder;
@class LSMediaItem;

@interface AudioPlayerViewController
  : LSCommonViewController <AVAudioPlayerDelegate>

@property (strong, nonatomic) IBOutlet UILabel *timerLabel;
@property (strong, nonatomic) IBOutlet UIButton *stopButton;
@property (strong, nonatomic) IBOutlet UIButton *replayButton;
@property (strong, nonatomic) IBOutlet UILabel *screenTitle;
@property (strong, nonatomic) IBOutlet UIView *playerButtonsView;

@property (strong, nonatomic) IBOutlet UIView *vSpacer1;
@property (strong, nonatomic) IBOutlet UIView *vSpacer2;
@property (strong, nonatomic) IBOutlet UIView *vSpacer3;

@property (strong, nonatomic) AudioRecorder *audioRecorder;
@property (strong, nonatomic) LSMediaItem *audioMediaItem;

- (IBAction)actionStopPlayback:(id)sender;
- (IBAction)actionStartPlayback:(id)sender;

// NOTE: This can eventually be removed
- (void)executeBackButton:(id)sender;

@end
