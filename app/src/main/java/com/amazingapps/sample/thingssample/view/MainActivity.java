package com.amazingapps.sample.thingssample.view;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.amazingapps.sample.thingssample.R;
import com.amazingapps.sample.thingssample.ndk.NativeHelper;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        NativeHelper helper = new NativeHelper();

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(helper.stringFromJNI());


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
