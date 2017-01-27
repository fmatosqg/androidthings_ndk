package com.amazingapps.sample.thingssample.ndk;

import android.os.SystemClock;
import android.util.Log;

/**
 * Created by fmatos on 25/01/2017.
 */

public class NativeHelper {

    private static final String TAG = NativeHelper.class.getSimpleName();

    public NativeHelper() {
        System.loadLibrary("native-lib");

//        System.loadLibrary("peripheralman");
        System.loadLibrary("androidthings_jni");
        Log.i(TAG,"Call native = " + stringFromJNI());

    }

//    public String stringFromJNI() {
//        return "java code";
//    }it st



    public native String stringFromJNI();
}
