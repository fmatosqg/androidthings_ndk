package com.amazingapps.sample.thingssample.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.amazingapps.sample.thingssample.R;
import com.amazingapps.sample.thingssample.controller.ServoController;
import com.amazingapps.sample.thingssample.ndk.NativeHelper;
import com.google.android.things.pio.PeripheralManagerService;

public class MainActivity extends AppCompatActivity {
    private ServoController servoController;

    // Used to load the 'native-lib' library on application startup.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        servoController = new ServoController(ServoController.getPwm0Pin(),20.0,2.0,1.0);

        NativeHelper helper = new NativeHelper();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(helper.stringFromJNI());

        Thread th = new Thread(new Runnable() {
            @Override
            public void run() {
                while(true) {
                    try {
                        Thread.sleep(1000);
                        servoController.setPosition(20);
                        Thread.sleep(1000);
                        servoController.setPosition(170);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        th.start();

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
