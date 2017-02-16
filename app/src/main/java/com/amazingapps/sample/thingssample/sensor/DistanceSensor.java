package com.amazingapps.sample.thingssample.sensor;

import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;

import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.GpioCallback;
import com.google.android.things.pio.PeripheralManagerService;

import java.io.IOException;

import static android.content.ContentValues.TAG;

/**
 * Created by fmatos on 25/01/2017.
 */

//https://github.com/vishal-android-freak/HC-SR04-AndroidThings-Library

public class DistanceSensor {

    private final int triggerPin;
    private final int echoPin;

    private Gpio trigger;
    private Gpio echo;

    private boolean isInitialized = false;

    private Float distanceCm;
    private Handler looperHandler;

    public DistanceSensor(int triggerPin, int echoPin) {

        this.echoPin = echoPin;
        this.triggerPin = triggerPin;

    }

    private void setup() {

        prepareLooper();

    }

    private void setupPins() {

        PeripheralManagerService service = new PeripheralManagerService();

        try {
            trigger = service.openGpio(getPin(triggerPin));
            trigger.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);

            echo = service.openGpio(getPin(echoPin));
            echo.setDirection(Gpio.DIRECTION_IN);
            echo.setEdgeTriggerType(Gpio.EDGE_BOTH);

            echo.registerGpioCallback(buildCallback());

            trigger.setActiveType(Gpio.ACTIVE_HIGH);
            echo.setActiveType(Gpio.ACTIVE_HIGH);
        } catch (IOException e) {
            e.printStackTrace();
        }


        if (trigger != null && echo != null) {
            isInitialized = true;
            distanceCm = -1.0f;
        }


    }

    private void prepareLooper() {

        final Thread looperThread = new Thread(new Runnable() {
            @Override
            public void run() {

                HandlerThread handlerThread = new HandlerThread("sr04handler");
                handlerThread.start();
                looperHandler = new Handler(handlerThread.getLooper());

                looperHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        setupPins();
                    }
                });
            }
        });


        looperThread.start();

    }


    private long timeEnd, timeStart;

    private GpioCallback buildCallback() {

        timeEnd = 0;
        timeStart = 0;
        GpioCallback callback = new GpioCallback() {
            @Override
            public boolean onGpioEdge(Gpio gpio) {

                try {
                    boolean val = echo.getValue();

                    if (!val) {
                        timeEnd = System.nanoTime();

                        long elapsed = timeEnd - timeStart;
                        double elapsedSec = (float) elapsed / 1000.0 * 1000.0 * 1000.0;

                        double distanceCm = elapsedSec * 340.0 / 2.0 * 100.0;
                        Log.i(TAG, "Elapsed " + elapsed + " ns / " + distanceCm + " cm");
                    } else {
                        timeStart = System.nanoTime();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return true;
            }
        };

        return callback;
    }

    private String getPin(int triggerPin) {
        return "BCM" + triggerPin;
    }


    public Float getDistance() {

        if (!isInitialized) {
            setup();
            return -1.0f;
        }

        looperHandler.post(new Runnable() {
            @Override
            public void run() {

                try {
                    trigger.setValue(false);
                    Thread.sleep(0, 2000);
                    trigger.setValue(true);
                    Thread.sleep(0, 10000);
                    trigger.setValue(false);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }
        });

        if (distanceCm > 1000) {
            return 0.0f;
        } else {
            return distanceCm;
        }
    }
}
