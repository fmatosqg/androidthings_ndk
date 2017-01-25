package com.amazingapps.sample.thingssample.controller;

/**
 * Created by fmatos on 25/01/2017.
 */

import android.util.Log;

import com.google.android.things.pio.PeripheralManagerService;
import com.google.android.things.pio.Pwm;

import java.io.IOException;

/**
 * Created by fabio.goncalves on 23/01/2017.
 */

public class ServoController {

    private static final String TAG = ServoController.class.getSimpleName();

    private Pwm pin;

    private final double periodMs;
    private final double maxTimeMs;
    private final double minTimeMs;

    private double pulseLenghtMs;

    public ServoController(String pin) {

        periodMs = 20;
        maxTimeMs = 2.5;
        minTimeMs = 0.5;

        setup(pin);
    }

    public ServoController(String pin, double periodMs, double maxTimeMs, double minTimeMs) {

        this.periodMs = periodMs;
        this.maxTimeMs = maxTimeMs;
        this.minTimeMs = minTimeMs;

        setup(pin);
    }

    private void setup(String pinName) {
        try {

            PeripheralManagerService service = new PeripheralManagerService();
            pin = service.openPwm(pinName);

            pin.setPwmFrequencyHz(1000.0d / periodMs);
            setPosition(90);
            pin.setEnabled(true);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * assumes that min position is 0 degrees and max is 180
     */
    public void setPosition(double degrees) {

        if (degrees > 90) {
            pulseLenghtMs = minTimeMs;
        } else {
            pulseLenghtMs = maxTimeMs;
        }

        pulseLenghtMs = (degrees / 180.0 * (maxTimeMs - minTimeMs)) + minTimeMs;

        if (pulseLenghtMs < minTimeMs) {
            pulseLenghtMs = minTimeMs;
        } else if (pulseLenghtMs > maxTimeMs) {
            pulseLenghtMs = maxTimeMs;
        }

        double dutyCycle = pulseLenghtMs / periodMs * 100.0;

        Log.i(TAG, "Duty cycle = " + dutyCycle + " pulse lenght = " + pulseLenghtMs);

        try {
            pin.setPwmDutyCycle(dutyCycle);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static String getPwm0Pin() {
        return "PWM0";
    }

    public static String getPwm1Pin() {
        return "PWM1";
    }
}
