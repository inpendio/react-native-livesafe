//
//  FileManager.h
//  LiveSafeMobileApp
//
//  Created by Demetris Christou on 6/12/13.
//  Copyright (c) 2013 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LiveSafeFileManager : NSObject

typedef NS_ENUM(NSUInteger, FileDeleteStatus) {
  fileDeleteSuccess,
  fileDeleteFail
};

@property (nonatomic, strong, nonnull) NSString *documentsDirectory;
@property (nonatomic, strong, nonnull) NSString *livesafeAssetDirectory;

- (id _Nonnull)init;
- (bool)fileExists:(NSString * _Nonnull)filepath;
- (FileDeleteStatus)deleteFile:(NSString * _Nonnull)filepath;
- (void)clearDirectoryContent:(NSString * _Nonnull)dirPath;
- (BOOL)addSkipBackupAttributeToItemAtPath:(NSString * _Nonnull)filePathString;

@end
