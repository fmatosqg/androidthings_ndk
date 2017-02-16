package com.amazingapps.sample.thingssample.ndk;

import android.util.Log;

import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.GpioCallback;
import com.google.android.things.pio.PeripheralManagerService;

import java.io.IOException;

/**
 * Created by fmatos on 25/01/2017.
 */

public class NativeHelper {

    private static final String TAG = NativeHelper.class.getSimpleName();

    public NativeHelper() {
        System.loadLibrary("sample");
        Log.i(TAG,"NDK library loaded");
    }

    private void runBenchmarks() {

        runJavaLoopbackTest();


        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                runLoopbackBenchmark();
                runWriteBenchmark();

            }


        });

        thread.start();

    }

    private void runJavaLoopbackTest() {
        PeripheralManagerService service = new PeripheralManagerService();

        String pinTriggerName = "BCM23";
        String pinName = "BCM22";

        try {
            Gpio mTrigger = service.openGpio(pinTriggerName);
            mTrigger.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);


            Gpio mButtonGpio = service.openGpio(pinName);
            mButtonGpio.setDirection(Gpio.DIRECTION_IN);
            mButtonGpio.setEdgeTriggerType(Gpio.EDGE_FALLING);
            mButtonGpio.registerGpioCallback(new GpioCallback() {
                @Override
                public boolean onGpioEdge(Gpio gpio) {
                    Log.i(TAG, "GPIO changed, button pressed");
                    // Return true to continue listening to events
                    return true;
                }
            });

            Log.i(TAG, "Start sleep");
            while ( true ) {
                mTrigger.setValue(true);
                Thread.sleep(40);
                mTrigger.setValue(false);
                Thread.sleep(1000);
            }
//            Log.i(TAG, "End sleep");
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


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

        for (int i = 0; i < 1000; i++) {
            Log.i(TAG, "Read i=" + i);
            benchmarkLoopback(23, 25);
        }

//        benchmarkLoopback(23,25);
//        benchmarkLoopback(23,25);

    }

    public native boolean benchmarkWrite(int pin, int count);

    public native int benchmarkRead(int pinNumber, int count);

    public native int benchmarkLoopback(int pinNumberOut, int pinNumberIn);


    public native String stringFromJNI();

    public native boolean exportPin();

    public native float sr04Distance(int triggerPin, int echoPin);

}
