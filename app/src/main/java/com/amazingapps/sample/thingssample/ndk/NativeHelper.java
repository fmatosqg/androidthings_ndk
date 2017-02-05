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

        runBenchmarks();

    }

    private void runBenchmarks() {

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                runWriteBenchmark();
                runLoopbackBenchmark();
            }
        });

        thread.start();

    }

    private void runWriteBenchmark() {
        Log.i(TAG, "Call native = " + stringFromJNI());


        Log.i(TAG, "Open pin " + exportPin());


        benchmarkWrite(1);
        benchmarkWrite(10000);
        benchmarkWrite(100000);
        benchmarkWrite(1000000);
        benchmarkWrite(2000000);

    }

    private void benchmarkWrite(int count) {
        long start = System.nanoTime();
        boolean isSuccess = benchmarkWrite(23, count);
        long end = System.nanoTime();

        if (isSuccess) {
            float elapsedMs = (end - start);
            elapsedMs /= 1000.0f;
            elapsedMs /= 1000.0f;

            float kHz = (float) count / elapsedMs;
            Log.i(TAG, count + " Iterations done in " + elapsedMs + " ms = " + kHz + " kHz");
        } else {
            Log.i(TAG, "do all FAILED! " + isSuccess);
        }

    }


    private void runLoopbackBenchmark() {

        Log.i(TAG, "Not implemented yet");
    }

    public native boolean benchmarkWrite(int pin, int count);

    public native int benchmarkRead(int pinNumber, int count);

    public native int benchmarkLoopback(int pinNumberOut, int pinNumberIn);


    public native String stringFromJNI();

    public native boolean exportPin();


}
