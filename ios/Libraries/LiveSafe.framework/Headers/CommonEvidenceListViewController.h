//
//  CommonEvidenceListViewController.h
//  LiveSafeAppProd
//
//  Created by Nicholas Fox on 10/20/15.
//  Copyright © 2015 LiveSafe. All rights reserved.
//

#import "EventReportMediaController.h"

@class LSTip;

@interface CommonEvidenceListViewController
  : LSCommonViewController <UITableViewDataSource, UITableViewDelegate>

@property (strong, nonatomic) IBOutlet UIView *containerView;
@property (strong, nonatomic) IBOutlet UITableView *evidenceTableView;
@property (strong, nonatomic) IBOutlet UILabel *promptLabel;

@property (strong, nonatomic) LSTip *tip;
@property (strong, nonatomic) NSMutableArray *evidenceArray;

@property (nonatomic) BOOL canEditMedia;

- (void)removeEvidenceItem:(LSMediaItem *)evidenceItem;

// NOTE: This can eventually be removed
- (void)executeBackButton:(id)sender;

@end
