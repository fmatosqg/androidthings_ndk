package com.amazingapps.sample.thingssample.domain;

import android.util.Log;

import com.amazingapps.sample.thingssample.domain.voice.VoiceSpeakerService;

/**
 * Created by fmatos on 17/02/2017.
 */
public class Quack {

    private static final String TAG = Quack.class.getSimpleName();

    private final VoiceSpeakerService voiceSpeakerService;
    private final Runnable timer;
    private boolean isSpeaking;

    private QuackState state;

    public Quack(VoiceSpeakerService voiceSpeakerService) {
        this.voiceSpeakerService = voiceSpeakerService;
        state = QuackState.UNKNOWN;
        timer = buildTimer();
        isSpeaking = false;
    }

    private Runnable buildTimer() {
        Runnable runnable = new Runnable() {
            @Override
            public void run() {

                try {
                    Thread.sleep(10000);

                    isSpeaking = false;
                    Log.i(TAG, "Idle");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };
        return runnable;
    }

    public void setDistance(double distance) {

        if (isSpeaking) {
            return;
        }

        if (distance == 0) {
            setState(QuackState.TOO_CLOSE);
        } else if (distance < 0) {
            setState(QuackState.UNKNOWN);
        } else if (distance < 40) {
            setState(QuackState.CLOSE);
        } else if (distance < 100) {
            setState(QuackState.MEDIUM);
        } else {
            setState(QuackState.FAR);
        }

    }

    private void setState(QuackState state) {
        if (this.state == state) {
            return;
        }

        Log.i(TAG, "Change state " + state);
        this.state = state;

        switch (state) {
            case TOO_CLOSE:
                speak("Quack, I'm a duck");
                break;
            case CLOSE:
                speak("wow! too much, are you a pervert?");
                break;
            case MEDIUM:
                speak("Noice");
                break;
            case FAR:
                speak("Come closer, are you shy?");
                break;
        }
        
    }

    private void speak(String text) {
        isSpeaking = true;
        voiceSpeakerService.speak(text);

        Thread thread = new Thread(timer);
        thread.start();
    }
}
