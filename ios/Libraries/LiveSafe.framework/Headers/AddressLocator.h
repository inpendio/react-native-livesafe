//
//  AddressLocator.h
//  LiveSafeAppProd
//
//  Created by J.R. Spencer on 4/2/14.
//  Copyright (c) 2014 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "GeolocationObject.h"

@interface AddressLocator : NSObject

- (void)updateLocationWithDistance:(CLLocation *)location
                        withTarget:(id)target
             withGeoLocationObject:(GeolocationObject *)geoLocation
                   successSelector:(SEL)successSelector
                   failureSelector:(SEL)failureSelector;

@end
