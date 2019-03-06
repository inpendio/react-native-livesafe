# react-native-livesafe

## Getting started

`$ npm install react-native-livesafe --save`

### Mostly automatic installation

`$ react-native link react-native-livesafe`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-livesafe` and add `RNLivesafe.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNLivesafe.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainApplication.java`
  - Add `import com.lane.rnlivesafe.RNLivesafePackage;` to the imports at the top of the file
  - Add `new RNLivesafePackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-livesafe'
  	project(':react-native-livesafe').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-livesafe/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-livesafe')
  	```

#### Windows
[Read it! :D](https://github.com/ReactWindows/react-native)

1. In Visual Studio add the `RNLivesafe.sln` in `node_modules/react-native-livesafe/windows/RNLivesafe.sln` folder to their solution, reference from their app.
2. Open up your `MainPage.cs` app
  - Add `using Livesafe.RNLivesafe;` to the usings at the top of the file
  - Add `new RNLivesafePackage()` to the `List<IReactPackage>` returned by the `Packages` method


## Usage
```javascript
import RNLivesafe from 'react-native-livesafe';

// TODO: What to do with the module?
RNLivesafe;
```
  