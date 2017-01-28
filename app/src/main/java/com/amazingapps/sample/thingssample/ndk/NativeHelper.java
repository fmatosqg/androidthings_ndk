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
        Log.i(TAG, "Call native = " + stringFromJNI());


        Log.i(TAG, "Open pin " + exportPin());


        doAllJava(10);
        doAllJava(10000);
        doAllJava(100000);

    }

    private void doAllJava(int count) {
        long start = System.nanoTime();
        boolean isSuccess = doAll(23, count, 0);
        long end = System.nanoTime();

        if (isSuccess ) {
            float elapsedMs = (end - start);
            elapsedMs /= 1000.0f;
            elapsedMs /= 1000.0f;

            float kHz = (float) count / elapsedMs;
            Log.i(TAG, count + " Iterations done in " + elapsedMs + " ms = " + kHz + " kHz");
        } else {
            Log.i(TAG, "do all FAILED! " + isSuccess);
        }

    }

    public native String stringFromJNI();

    public native boolean exportPin();

    public native boolean doAll(int pin, int count, int sleeMs);
}
