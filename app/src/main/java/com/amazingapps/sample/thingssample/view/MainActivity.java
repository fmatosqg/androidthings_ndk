package com.amazingapps.sample.thingssample.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.amazingapps.sample.thingssample.R;
import com.amazingapps.sample.thingssample.controller.ServoController;
import com.amazingapps.sample.thingssample.domain.Quack;
import com.amazingapps.sample.thingssample.domain.voice.VoiceSpeakerService;
import com.amazingapps.sample.thingssample.ndk.NativeHelper;
import com.amazingapps.sample.thingssample.sensor.DistanceSensor;
import com.google.android.things.pio.PeripheralManagerService;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    private DistanceSensor distanceSensor;
    private Quack quack;
    private VoiceSpeakerService voiceSpeakerService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        distanceSensor = new DistanceSensor(17, 27);

        voiceSpeakerService = new VoiceSpeakerService(this);
        quack = new Quack(voiceSpeakerService);
        readDistance();
    }

    private void readDistance() {

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {

                while (true) {
                    try {
                        Thread.sleep(1000);
                        Float distance = distanceSensor.getDistance();

                        quack.setDistance(distance);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });


        thread.start();
    }

}
