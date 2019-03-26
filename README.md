# react-native-livesafe

## Getting started

`$ npm install react-native-livesafe --save`

`$ react-native link react-native-livesafe`



#### iOS

1. Add the following Pods to the project's Podfile

```
  pod 'Alamofire', '4.7.3'
  pod 'SwiftyJSON', '4.1.0'
  pod 'ObjectMapper', '3.3.0'
  pod 'lottie-ios', '2.5.0'
  # pod 'GoogleMaps', '2.6.0' only if using SafeMap
  pod 'SDWebImage', '4.3.2'
```

*alternatively if not using CocoaPods, (**or not using use_frameworks! in Podfile, you'll need the framework (.framework) files to be embedded**), you can download the binary for each framework and link them manually*

3. `pod install`

2. Add the LiveSafe frameworks into embedded binaries

4. Add the following lines to projectSettings > Target > Build Settings > **Framework Search Paths**

```
  "${PODS_CONFIGURATION_BUILD_DIR}/Alamofire"
  "${PODS_CONFIGURATION_BUILD_DIR}/ObjectMapper"
  "${PODS_CONFIGURATION_BUILD_DIR}/SDWebImage"
  "${PODS_ROOT}/GoogleMaps/Maps/Frameworks"
  "${PODS_ROOT}/GoogleMaps/Base/Frameworks"
  "${PODS_CONFIGURATION_BUILD_DIR}/lottie-ios"
  "${PODS_CONFIGURATION_BUILD_DIR}/SwiftyJSON"
```

5. After running `yarn add react-native-livesafe` manually link the xcode project: right click the Libraries folder in your project > Add files > go to node_modules/react-native-livesafe/ios > add the **.xcodeproj** file

6. Click the newly added project and in **Build Phases** remove the old references to Pods and add your own.

7. In your Target's Build Phases add the libRNLiveSafe.a under Link Binary with Libraries

##### AppDelegate Config

You'll need to change your AppDelegate to make sure LiveSafe's sdk custom screens can be pushed to your App's UINavigatorViewController.

To start you'll need to change your `window.rootViewController` to be a `UINavigatorViewController` instead of a `UIViewController`. Doing this will make your application show a native navigation bar, to hide this you'll need to create a custom `UIViewController` class that hides it automatically.

###### AppDelegate.h
```
//AppDelegate.h

@interface CustomViewController : UIViewController
- (void) viewDidAppear:(BOOL)animated;
@end

@interface AppDelegate : UIResponder <UIApplicationDelegate, UINavigationControllerDelegate>

@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) CustomViewController *rootViewController;

@end

```
###### AppDelegate.m
```
#import "AppDelegate.h"

#import <React/RCTBundleURLProvider.h>
#import <React/RCTRootView.h>
#import <Firebase.h>

@implementation CustomViewController

- (void) viewWillAppear:(BOOL)animated {
    AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    ((UINavigationController*) delegate.rootViewController).navigationBarHidden = YES;
}

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  NSURL *jsCodeLocation;
  jsCodeLocation = [[RCTBundleURLProvider sharedSettings] jsBundleURLForBundleRoot:@"index" fallbackResource:nil];

  RCTRootView *rootView = [[RCTRootView alloc] initWithBundleURL:jsCodeLocation
                                                      moduleName:@"YOUR_APP_MODULE_NAME"
                                               initialProperties:nil
                                                   launchOptions:launchOptions];
  rootView.backgroundColor = [[UIColor alloc] initWithRed:1.0f green:1.0f blue:1.0f alpha:1];

  self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  CustomViewController *rootViewController = [CustomViewController new];
  rootViewController.view = rootView;
  UINavigationController * navController = [[UINavigationController alloc]  initWithRootViewController:rootViewController];
  [navController setDelegate:self];
  self.window.rootViewController = navController;
  self.rootViewController = navController;
  [self.window makeKeyAndVisible];
  return YES;
}

@end

```

Lastly, make sure you to import your `AppDelegate.h` in the `RNLiveSafe` Project's header file.

#### Android

Add to your project build.gradle file:

```
allprojects {
    repositories {
				...
        maven {
            url "https://jitpack.io"
            credentials { username "YOUR_JITPACK_API_KEY" }
        }
    }
}
```


## Usage
### API
```javascript
import LiveSafe from 'react-native-livesafe';
LiveSafe.init("YOUR_CLIENT_KEY","YOUR_CLIENT_SECRET");

/**
 * Currently not working on android 
 */
LiveSafe.showMap();

/**
 * Return list of Tips. Check TipType for model
 */
LiveSafe.getTipTypes();

/**
 * Opens activity with history of your tips
 */
LiveSafe.getTipHistory();

/**
 * @param {Object} - tip
 * Check TipType model for excactly what you need to send.
 */
LiveSafe.submitTip(tip);

/**
 * Opens activity for auth
 */
LiveSafe.authentication();

/**
 * @return {Promise} with bool is user logged in
 */
LiveSafe.isLoggedin();

/**
 * @param {String} - number of yout organization security "+122334455"
 */
LiveSafe.callOrganizationSecurity(number);

/**
 * @param {String} - number of yout local security "911"
 */
LiveSafe.callLocalEmergencyService(number);

/**
 * Opens activity for messaging
 */
LiveSafe.messageOrganizationSecurity();
```
  
```
// TipType Model
     *        value - Number - required
     *        name - String - required
     *        icon - String
     *        mapIcon - Number
     *        hintText - String
     *        chatText - String
```

```
// Tip Model
     *        text - String - required
     *        isAnonymous - Boolean
     *        dateCreated - Date
     *        longitude - Number
     *        latitude - Number
     *        tipType - Number
     *        uuid - String

```
