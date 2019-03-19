//
//  LSWebViewController.h
//  LiveSafeMobileApp
//
//  Created by Demetris Christou on 4/19/13.
//  Copyright (c) 2013 LiveSafe. All rights reserved.
//

#import "LSCommonViewController.h"
#import <UIKit/UIKit.h>

@interface LSWebViewController : LSCommonViewController <UIWebViewDelegate>

@property (strong, nonatomic) IBOutlet UIWebView *webView;

@property (nonatomic, strong) NSURL *url;

@end
