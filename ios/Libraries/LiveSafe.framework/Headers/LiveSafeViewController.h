//
//  LiveSafeViewController.h
//  LiveSafe
//
//  Created by Nicholas Fox on 6/5/16.
//  Copyright © 2016 LiveSafe. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LiveSafeViewController : UIViewController

@property (strong, nonatomic, nullable) IBOutlet UIView *lsBrandingView;
@property (strong, nonatomic, nullable) IBOutlet NSLayoutConstraint *lsBrandingViewHeightConstraint;
@property (strong, nonatomic, nullable) IBOutlet UIImageView *livesafeLogoImage;

@end
