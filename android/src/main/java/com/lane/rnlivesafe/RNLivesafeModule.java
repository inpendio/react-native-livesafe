package com.lane.rnlivesafe;

import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.BaseActivityEventListener;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.livesafemobile.livesafesdk.auth.LiveSafeAuth;
import com.livesafemobile.livesafesdk.base.LiveSafeSDK;
import com.livesafemobile.livesafesdk.base.Organization;
import com.livesafemobile.livesafesdk.common.Result;
import com.livesafemobile.livesafesdk.login.RegisterUserActivity;
import com.livesafemobile.livesafesdk.tip.EmergencyCall;
import com.livesafemobile.livesafesdk.tip.ReportTipActivity;
import com.livesafemobile.livesafesdk.tip.Tip;
import com.livesafemobile.livesafesdk.tip.TipHistoryActivity;
import com.livesafemobile.livesafesdk.tip.TipType;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import rx.functions.Action1;
import rx.functions.Func1;


public class RNLivesafeModule extends ReactContextBaseJavaModule {

    private static final String TAG = "LiveSafeModule";

    private final ReactApplicationContext reactContext;
    private Promise loginPromise;

    public void setLoginPromise(Promise promise) {
        this.loginPromise = promise;
    }

    private final ActivityEventListener mActivityEventListener = new BaseActivityEventListener() {

        @Override
        public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent intent) {
            if (requestCode == RegisterUserActivity.REGISTER_USER_REQUEST_CODE) {
                if (loginPromise != null) {
                    if (resultCode == 0) {
                        loginPromise.resolve(new Boolean(false));
                    } else if (resultCode == -1) {
                        loginPromise.resolve(new Boolean(true));
                    }
                }
            }
        }
    };

    public RNLivesafeModule(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        reactContext.addActivityEventListener(mActivityEventListener);
    }

    @Override
    public String getName() {
        return "RNLivesafe";
    }

    @ReactMethod
    public void init(String key, String secret, String fcmToken, final Promise promise) {
        Log.i(TAG, "init");
        LiveSafeSDK.create(this.reactContext, new LiveSafeAuth(key, secret));
        LiveSafeSDK.getInstance().startSession(
                new Result<Void>() {
                    @Override
                    public void call(Void aVoid) {
                        Log.i(TAG, "Session success!!");
                        promise.resolve(new String("Logged in"));
                    }
                },
                new Result<Throwable>() {
                    @Override
                    public void call(Throwable throwable) {
                        Log.w(TAG, "Session fail!!");
                        promise.reject(throwable);
                    }
                },
                null
        );
    }

    @ReactMethod
    public void showMap() {
        Activity currentActivity = getCurrentActivity();
        Intent intent = SafeMapActivity.createIntent(this.reactContext, null);
        currentActivity.startActivity(intent);
    }

    @ReactMethod
    public void getTipTypes(Promise promise) {
        LiveSafeSDK liveSafe = LiveSafeSDK.getInstance();
        Organization organization = liveSafe.getOrganization();
        List<TipType> tipTypes = organization.getTipTypes();
        WritableArray arr = Arguments.createArray();

        if (tipTypes != null) {
            for (TipType tip : tipTypes) {
                WritableMap map = Arguments.createMap();
                map.putInt("value", tip.getValue());
                map.putString("name", tip.getName());
                map.putString("icon", tip.getIcon());
                map.putString("mapIcon", tip.getMapIcon());
                map.putString("hintText", tip.getHintText());
                map.putString("chatText", tip.getChatText());
                arr.pushMap(map);
            }
        }

        promise.resolve(arr);
    }

    @ReactMethod
    public void showTipHistory() {
        Activity currentActivity = getCurrentActivity();
        Intent intent = TipHistoryActivity.createIntent(this.reactContext);
        currentActivity.startActivity(intent);
    }

    /**
     * @param tipTypeObject ReadableMap - a js object containing following fields should be passed as param:
     *                      value - Number - required
     *                      name - String - required
     *                      icon - String
     *                      mapIcon - Number
     *                      hintText - String
     *                      chatText - String
     */
    @ReactMethod
    public void submitTip(ReadableMap tipTypeObject) {
        TipType tipType = new TipType(
                tipTypeObject.getInt("value"),
                tipTypeObject.getString("name"),
                tipTypeObject.hasKey("icon") ? tipTypeObject.getString("icon") : "",
                tipTypeObject.hasKey("mapIcon") ? tipTypeObject.getString("mapIcon") : "",
                tipTypeObject.hasKey("hintText") ? tipTypeObject.getString("hintText") : "",
                tipTypeObject.hasKey("chatText") ? tipTypeObject.getString("chatText") : ""
        );
        Activity currentActivity = getCurrentActivity();
        Intent intent = ReportTipActivity.createIntent(this.reactContext, tipType);
        currentActivity.startActivity(intent);
    }

    @ReactMethod
    public void authentication(Promise promise) {
        Activity currentActivity = getCurrentActivity();
        Intent intent = RegisterUserActivity.createIntent(this.reactContext);
        currentActivity.startActivityForResult(intent, RegisterUserActivity.REGISTER_USER_REQUEST_CODE);
        this.setLoginPromise(promise);
    }

    @ReactMethod
    public void updateUserLocation() {
        LiveSafeSDK liveSafe = LiveSafeSDK.getInstance();
    }

    @ReactMethod
    public void emergencyOptions() {

    }

    @ReactMethod
    public void isLoggedIn(Promise promise) {
        promise.resolve(new Boolean(LiveSafeSDK.getInstance().isUserRegistered()));
    }

    @ReactMethod
    public void getEmergencies() {

    }

    @ReactMethod
    public void callOrganizationSecurity(String number) {
        EmergencyCall.Builder builder = new EmergencyCall.Builder();
        builder.setMessage("Calling").setNumber(number).setTipTypeId(TipType.EVENT_TYPE_CALL_POLICE).setTrack(true);
        LiveSafeSDK.getInstance().makeCall(builder.build(), new Result<Tip>() {
            @Override
            public void call(Tip tip) {
                Log.i(TAG, "called success");
            }
        }, new Result<Exception>() {
            @Override
            public void call(Exception e) {
                Log.i(TAG, "called fail");
            }
        });
    }

    @ReactMethod
    public void callLocalEmergencyService(String number) {
        EmergencyCall.Builder builder = new EmergencyCall.Builder();
        builder.setMessage("Calling").setNumber(number).setTipTypeId(TipType.EVENT_TYPE_CALL_POLICE).setTrack(true);
        LiveSafeSDK.getInstance().makeCall(builder.build(), new Result<Tip>() {
            @Override
            public void call(Tip tip) {
                Log.i(TAG, "called success");
            }
        }, new Result<Exception>() {
            @Override
            public void call(Exception e) {
                Log.i(TAG, "called fail");
            }
        });
    }

    @ReactMethod
    public void messageOrganizationSecurity() {
        Activity currentActivity = getCurrentActivity();
        Intent intent = ReportTipActivity.createEmergencyMessageIntent(this.reactContext, "users_location_will_be_shared");
        currentActivity.startActivity(intent);
    }

    @ReactMethod
    public void endSession() {
        LiveSafeSDK.getInstance().endSession(
                new Result<Void>() {
                    @Override
                    public void call(Void v) {
                        Log.i(TAG, "end session succcess");
                    }
                },
                new Result<Throwable>() {
                    @Override
                    public void call(Throwable throwable) {
                        Log.w(TAG, "end session failed");
                    }
                });
    }


    @ReactMethod
    public void getOrganization(Integer orgId, final Promise promise) {
        // There is no getOrganization on Android.

        try {
            Organization org = new Organization(orgId);
            promise.resolve(org.getName());
        } catch (Exception err) {
            promise.reject(err);
        }
    }

    @ReactMethod
    public void setOrganization(Integer orgId, final Promise promise) {
        LiveSafeSDK.getInstance().setOrganization(orgId,
                new Result<Integer>() {
                    @Override
                    public void call(Integer orgId) {
                        Log.i(TAG, "setOrganization success");
                        promise.resolve(orgId);
                    }
                },
                new Result<Throwable>() {
                    @Override
                    public void call(Throwable throwable) {
                        Log.w(TAG, "setOrganization failed");
                        promise.reject(throwable);
                    }
                });
    }

    @ReactMethod
    public void stopActiveTracking() {
        // not implemented on android?
    }

}