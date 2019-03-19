//
//  TipUtil.h
//  LiveSafe
//
//  Created by Demetris Christou on 6/9/16.
//  Copyright © 2016 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LSTip;
@class LSMediaItem;

@interface TipUtil : NSObject

+ (NSString *_Nonnull)createUniqueFilename:(NSString * _Nonnull)mediaType;
+ (void)deleteLocalMedia:(LSTip * _Nonnull)tip;
+ (void)deleteMediaFile:(LSMediaItem * _Nonnull)mediaItem;
+ (NSMutableArray * _Nonnull)uuidOfUnsubmittedReports;

@end
