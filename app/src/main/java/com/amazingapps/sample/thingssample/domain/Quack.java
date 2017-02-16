package com.amazingapps.sample.thingssample.domain;

import com.amazingapps.sample.thingssample.domain.voice.VoiceSpeakerService;

/**
 * Created by fmatos on 17/02/2017.
 */
public class Quack {
    private final VoiceSpeakerService voiceSpeakerService;
    private Float distance;

    public Quack(VoiceSpeakerService voiceSpeakerService) {
        this.voiceSpeakerService = voiceSpeakerService;
    }

    public void setDistance(Float distance) {
        this.distance = distance;

        voiceSpeakerService.speak("hi");
    }
}
