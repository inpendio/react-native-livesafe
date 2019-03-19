//
//  TipSubmitConstants.h
//  LiveSafe
//
//  Created by Demetris Christou on 4/28/16.
//  Copyright © 2016 LiveSafe. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TipSubmitConstants : NSObject

// Steps
typedef enum
{
  TIP_SUBMIT_STEP_BEGINNING = 0,
  TIP_SUBMIT_STEP_ADD_EVENT = 1,
  TIP_SUBMIT_STEP_ADD_MEDIA_ITEM = 5,
  TIP_SUBMIT_STEP_CANCEL = 6,
  TIP_SUBMIT_STEP_COMPLETION = 7,
} TipSubmitStepType;

// Status
typedef enum
{
  TIP_SUBMIT_STATUS_NOT_START = 0,
  TIP_SUBMIT_STATUS_START = 8,
  TIP_SUBMIT_STATUS_SUCCESS = 9,
  TIP_SUBMIT_STATUS_FAIL = 10,
  TIP_SUBMIT_STATUS_CANCELED = 11,
} TipSubmitStatusType;

extern NSString *const TIP_SUBMIT_ADDEVENT_RESPONSE_JSON;
extern NSString *const TIP_SUBMIT_ADDEVENT_SERVICE_RESPONSE;

@end
