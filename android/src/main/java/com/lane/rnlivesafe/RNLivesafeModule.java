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
import com.livesafemobile.safetymap.SafeMapActivity;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import rx.functions.Action1;
import rx.functions.Func1;


public class RNLivesafeModule extends ReactContextBaseJavaModule {

    private static final String TAG = "LiveSafeModule";
    public static final int LS_LOGIN_ACTIVITY = 299933587;
    public static final int LS_REPORT_TIP = 299933588;
    public static final int LS_MESSAGE_ORGANIZATION_SECURITY = 299933589;

    private final ReactApplicationContext reactContext;

    private final ActivityEventListener mActivityEventListener = new BaseActivityEventListener() {

        @Override
        public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent intent) {
            if (requestCode == LS_LOGIN_ACTIVITY) {
                Log.i(TAG, "LOGIN result came...");
            }else if(requestCode == LS_REPORT_TIP){
                Log.i(TAG, "REPORT TIP result came...");
            }else if(requestCode == LS_MESSAGE_ORGANIZATION_SECURITY){
                Log.i(TAG, "LS_MESSAGE_ORGANIZATION_SECURITY result came...");
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
    public void init(String key, String secret, final Promise promise) {
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
    public void showMap(){
        Activity currentActivity = getCurrentActivity();
        Intent intent = SafeMapActivity.createIntent(this.reactContext, null);
        currentActivity.startActivity(intent);
    }

    @ReactMethod
    public void getTipTypes(Promise promise){
        LiveSafeSDK lssdk = LiveSafeSDK.getInstance();
        Organization o = lssdk.getOrganization();
        List<TipType> tt = o.getTipTypes();
        WritableArray arr = Arguments.createArray();
        
        for(TipType t : tt){
            WritableMap map = Arguments.createMap();
            map.putInt("value", t.getValue());
            map.putString("name", t.getName());
            map.putString("icon",t.getIcon());
            map.putString("mapIcon",t.getMapIcon());
            map.putString("hintText",t.getHintText());
            map.putString("chatText", t.getChatText());
            arr.pushMap(map);
        }
        promise.resolve(arr);
    }

    @ReactMethod
    public void getTipHistory(){
        Activity currentActivity = getCurrentActivity();
        Intent intent = TipHistoryActivity.createIntent(this.reactContext);
        currentActivity.startActivity(intent);
    }

    /**
     * @param tipTypeObject ReadableMap - a js object containing following fields should be passed as param:
     *        value - Number - required
     *        name - String - required
     *        icon - String
     *        mapIcon - Number
     *        hintText - String
     *        chatText - String
     * */
    @ReactMethod
    public void submitTip(ReadableMap tipTypeObject){
        TipType tt = new TipType(
                tipTypeObject.getInt("value"),
                tipTypeObject.getString("name"),
                tipTypeObject.hasKey("icon") ? tipTypeObject.getString("icon") : "",
                tipTypeObject.hasKey("mapIcon") ? tipTypeObject.getString("mapICon"): "",
                tipTypeObject.hasKey("hintText") ? tipTypeObject.getString("hintText") : "",
                tipTypeObject.hasKey("chatText") ? tipTypeObject.getString("chatText") : ""
        );
        Activity currentActivity = getCurrentActivity();
        Intent intent = ReportTipActivity.createIntent(this.reactContext, tt);
        currentActivity.startActivityForResult(intent, LS_REPORT_TIP);
    }

    @ReactMethod
    public void authentication(Promise promise){
        Activity currentActivity = getCurrentActivity();
        Intent intent = RegisterUserActivity.createIntent(this.reactContext);
        currentActivity.startActivityForResult(intent, LS_LOGIN_ACTIVITY);
        // FIXME: make sure this returns true/false if auth is invalid
        promise.resolve(true);
    }

    @ReactMethod
    public void updateUserLocation(){

    }

    @ReactMethod
    public void emergencyOptions(){
        
    }

    @ReactMethod
    public void isLoggedin(Promise promise){
        promise.resolve(new Boolean(LiveSafeSDK.getInstance().isUserRegistered()));
    }

    @ReactMethod
    public void getEmergencies(){

    }

    @ReactMethod
    public void callOrganizationSecurity(String number){
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
    public void callLocalEmergencyService(String number){
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
    public void messageOrganizationSecurity(){
        Activity currentActivity = getCurrentActivity();
        Intent intent = ReportTipActivity.createEmergencyMessageIntent(this.reactContext, "users_location_will_be_shared");
        currentActivity.startActivityForResult(intent, LS_MESSAGE_ORGANIZATION_SECURITY);
    }

    @ReactMethod
    public void switchOrganization(Number orgId, final Promise promise){
      LiveSafeSDK.getInstance().setOrganization(futureOrgID, organization -> {
          promise.resolve(true)
      },
    }

}
