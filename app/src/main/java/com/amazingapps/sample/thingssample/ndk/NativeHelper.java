package com.amazingapps.sample.thingssample.ndk;

import android.os.SystemClock;
import android.util.Log;

/**
 * Created by fmatos on 25/01/2017.
 */

public class NativeHelper {

    private static final String TAG = NativeHelper.class.getSimpleName();

    public NativeHelper() {
        System.loadLibrary("sample");
        Log.i(TAG,"Call native = " + stringFromJNI());



        Log.i(TAG,"Open pin " +  exportPin());


        long start = System.nanoTime();

        Log.i(TAG,"do all " +  doAll(0,0,0));

        long end = System.nanoTime();

        float elapsedMs = (end-start);
        elapsedMs /= 1000.0f;
        elapsedMs /= 1000.0f;

        Log.i(TAG,"Iterations done in " + elapsedMs);

    }

    public native String stringFromJNI();

    public native boolean exportPin();

    public native boolean doAll(int pin,int count, int sleeMs);
}
