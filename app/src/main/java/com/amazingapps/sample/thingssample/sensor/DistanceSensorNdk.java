package com.amazingapps.sample.thingssample.sensor;

import com.amazingapps.sample.thingssample.ndk.NativeHelper;
import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.GpioCallback;
import com.google.android.things.pio.PeripheralManagerService;

/**
 * Created by fmatos on 25/01/2017.
 */

//https://github.com/vishal-android-freak/HC-SR04-AndroidThings-Library

public class DistanceSensorNdk extends DistanceSensor {

    private final int triggerPin;
    private final int echoPin;

    private NativeHelper nativeHelper;
    private boolean isInitialized;

    public DistanceSensorNdk(int triggerPin, int echoPin) {

        super(0, 0);
        this.echoPin = echoPin;
        this.triggerPin = triggerPin;

        setup();
    }

    private void setup() {
        nativeHelper = new NativeHelper();

        if (nativeHelper != null) {
            isInitialized = true;
        }


    }

    public Float getDistance() {

        return nativeHelper.sr04Distance(triggerPin, echoPin);
    }
}
