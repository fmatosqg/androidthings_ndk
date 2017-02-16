package com.amazingapps.sample.thingssample.domain.voice;

import android.content.Context;
import android.os.Build;
import android.speech.tts.TextToSpeech;
import android.speech.tts.Voice;
import android.util.Log;

import java.util.Locale;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by fmatos on 5/02/2017.
 */
public class VoiceSpeakerService {

    private final static String TAG = VoiceSpeakerService.class.getSimpleName();

    private TextToSpeech textToSpeech;
    final AtomicBoolean isInitialized;

    public VoiceSpeakerService(Context applicationContext) {


        isInitialized = new AtomicBoolean(false);


        textToSpeech = new TextToSpeech(applicationContext, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                if (status != TextToSpeech.ERROR) {
                    textToSpeech.setLanguage(Locale.UK);
                    textToSpeech.setSpeechRate(0.7f);
                    showInfo();
                    isInitialized.set(true);

                }
            }
        });


    }

    private void waitForEngineReady() {

        if (isInitialized.get()) {
            return;
        }

        try {
            int count = 100;
            while (!isInitialized.get() && count > 0) {
                Log.i(TAG, "Wait init " + count);
                //isInitialized.wait(1000);
                Thread.sleep(100);
                count--;

            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void speak(String message) {

        waitForEngineReady();

        Log.i(TAG, "Speaking now:  " + message);
        textToSpeech.speak(message, TextToSpeech.QUEUE_FLUSH, null);

    }

    private void showInfo() {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {

            for (TextToSpeech.EngineInfo engine : textToSpeech.getEngines()) {
//                androidLogger.i(TAG, "Name " + engine.name + ", " + engine.label);
            }

            if (textToSpeech.getVoices() != null) {

                for (Voice voice : textToSpeech.getVoices()) {
//                    androidLogger.i(TAG, "Voice " + voice.getName() + ", " + voice.describeContents());
                    if ("en-au-x-afh-network".equals(voice.getName())) { //en-au-x-afh-network en-au-x-afh-local
                        textToSpeech.setVoice(voice);
                        Log.i(TAG, "Set Voice " + voice.getName());
                    }
                }
            }

        }
    }
}
