# react-native-livesafe

## Getting started

`$ npm install react-native-livesafe --save`

`$ react-native link react-native-livesafe`



#### iOS


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
LiveSafe.getTips();

/**
 * Opens activity with history of your tips
 */
LiveSafe.showTipHistory();

/**
 * @param {Object} - tip
 * Check TipType model for excactly what you need to send.
 */
LiveSafe.submitTip(tip);

/**
 * Opens activity for auth
 */
LiveSafe.authentification();

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
LiveSafe.messageOrganzationSecurity();
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
