//
//  GeolocationObject.h
//  CrimePush
//
//  Created by Antonio Jr Atamosa on 6/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GeolocationObject : NSObject

@property (nonatomic, strong, nullable) NSString *street;
@property (nonatomic, strong, nullable) NSString *streetNumber;
@property (nonatomic, strong, nullable) NSString *city;
@property (nonatomic, strong, nullable) NSString *state;
@property (nonatomic, strong, nullable) NSString *postalCode;

- (nullable NSString *)oneLineAddress;

@end
