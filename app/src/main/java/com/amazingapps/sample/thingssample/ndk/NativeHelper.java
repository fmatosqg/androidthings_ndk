package com.amazingapps.sample.thingssample.ndk;

import android.util.Log;

/**
 * Created by fmatos on 25/01/2017.
 */

public class NativeHelper {

    private static final String TAG = NativeHelper.class.getSimpleName();

    public NativeHelper() {
        System.loadLibrary("sample");
        Log.i(TAG,"Call native = " + stringFromJNI());

    }

    public native String stringFromJNI();
}
