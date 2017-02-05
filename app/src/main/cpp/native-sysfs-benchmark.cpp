//
// Created by Fabio on 5/02/2017.
//


#include <jni.h>
#include <time.h>

#include "native-sysfs.h"
#include "native-sysfs-listener-client.h"
#include "native-sysfs-asynchronous.h"

extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_exportPin(JNIEnv *env, jobject instance) {

    int fd = GPIOOpenFd(23, DIRECTION_OUT);

    GPIOCloseFd(23, fd);
    if (fd > 0) {
        return true;
    } else {
        return false;
    }
}

extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_benchmarkWrite__II(JNIEnv *env,
                                                                             jobject instance,
                                                                             jint pin, jint count) {

    int pinNumber = pin;
    bool isSuccess = false;

    int fd = GPIOOpenFd(pinNumber, DIRECTION_OUT);

    if (fd > 0) {

        if (GPIOWriteFd(fd, WRITE_HIGH)) {
            for (int i = 0; i < count; i++) {
                GPIOWriteFd(fd, WRITE_LOW);
                GPIOWriteFd(fd, WRITE_HIGH);
            }
            isSuccess = true;
        }

        GPIOCloseFd(pinNumber, fd);
    }

    return isSuccess;
}

extern "C" jint
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_benchmarkRead(JNIEnv *env,
                                                                        jobject instance,
                                                                        jint pinNumber,
                                                                        jint count) {

    // TODO

}

extern "C" jint
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_benchmarkLoopback(JNIEnv *env,
                                                                            jobject instance,
                                                                            jint pinNumberOut,
                                                                            jint pinNumberIn) {

    startWritingThread(pinNumberOut);
    startReadingThread(pinNumberIn);

    return 0;

}

int aaa(int pinNumberOut, int pinNumberIn) {
    int pinOutputFd = GPIOOpenFd(pinNumberOut, DIRECTION_OUT);
    int pinInputFd = GPIOOpenFd(pinNumberIn, DIRECTION_IN);


    if (pinOutputFd < 0 || pinInputFd < 0) {
        LOGE("Failed to open necessary pins");
        return -1;
    }

    int sleepMs = 200;
    clock_t start = clock();
    for (int i = 0; i < 100; i++) {
        GPIOWriteFd(pinOutputFd, WRITE_HIGH);
        usleep(sleepMs * 1000);
        GPIOReadFd(pinInputFd);
        usleep(sleepMs * 1000);
        GPIOWriteFd(pinOutputFd, WRITE_LOW);
        usleep(sleepMs * 1000);

    }

//    LOGE()
//    for (int i = 0; i < 1000; i++) {
//
//    }
    clock_t end = clock();

    GPIOCloseFd(pinNumberOut, pinOutputFd);
//    GPIOCloseFd(pinNumberIn, pinInputFd);

    clock_t timeElapsed_us = end - start;
    float fTimeElapsed_s = timeElapsed_us;
    fTimeElapsed_s = fTimeElapsed_s / 1000.0f / 1000.0f;
    float equivalentHz = 1000.0f / fTimeElapsed_s;

    LOGD("Time elapsed was ~ %f kHz / %ld us ", equivalentHz / 1000.0f, timeElapsed_us);

    return
            timeElapsed_us;

}


int writeBenchmarkNative() {
    int pin23 = GPIOOpenFd(23, DIRECTION_OUT);

    if (pin23 < 0) {
        return -1;
    }

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        GPIOWriteFd(pin23, WRITE_HIGH);
        GPIOWriteFd(pin23, WRITE_LOW);
    }
    clock_t end = clock();

    GPIOCloseFd(23, pin23);

    clock_t timeElapsed_us = end - start;
    float fTimeElapsed_s = timeElapsed_us;
    fTimeElapsed_s = fTimeElapsed_s / 1000.0f / 1000.0f;
    float equivalentHz = 1000.0f / fTimeElapsed_s;

    LOGD("Time elapsed was ~ %f kHz / %ld us ", equivalentHz / 1000.0f, timeElapsed_us);

    return timeElapsed_us;

}

