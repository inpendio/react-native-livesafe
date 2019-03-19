//
//  EventReportMediaController.h
//  LiveSafeAppProd
//
//  Created by Demetris Christou on 12/16/14.
//  Copyright (c) 2014 LiveSafe. All rights reserved.
//

#import "LSCommonViewController.h"
#import <Foundation/Foundation.h>

@class LSMediaItem;

@interface EventReportMediaController : NSObject

// The following properties are defined as weak to prevent
// any circular dependencies (i.e. parent pointing to child and child
// pointing to parent) that would cause the objects to never be released
// from memory.
@property (nonatomic, weak) LSCommonViewController *sourceViewController;
@property (nonatomic, weak) UIView *parentViewOfActivityIndicator;

- (id)initWithViewController:(LSCommonViewController *)viewController
  activityIndicatorContainerView:(UIView *)containerView;

- (void)downloadMediaItem:(LSMediaItem *)mediaItem
               completion:(void (^)(LSMediaItem *mediaItem))completionHandler;
- (void)showMediaItem:(LSMediaItem *)mediaItem;
- (void)cancel;

- (void)cleanup;

@end
