package com.lane.rnlivesafe;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;
import com.livesafemobile.livesafesdk.auth.LiveSafeAuth;
import com.livesafemobile.livesafesdk.base.LiveSafeSDK;
import com.livesafemobile.livesafesdk.common.Result;
import android.util.Log;

public class RNLivesafeModule extends ReactContextBaseJavaModule {

    private final ReactApplicationContext reactContext;

    public RNLivesafeModule(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
    }

    @Override
    public String getName() {
        return "RNLivesafe";
    }

    @ReactMethod
    public void init(String key, String secret) {
        LiveSafeSDK.create(this.reactContext, new LiveSafeAuth(key, secret));
        LiveSafeSDK.getInstance().startSession(
                new Result<Void>() {
                    @Override
                    public void call(Void aVoid) {
                        Log.i("LiveSafe", "Session success!!");
                    }
                },
                new Result<Throwable>() {
                    @Override
                    public void call(Throwable throwable) {
                        Log.w("LiveSafe", "Session fail!!");
                    }
                },
                null
        );
    }
}
