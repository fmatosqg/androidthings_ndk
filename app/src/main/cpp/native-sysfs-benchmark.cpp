//
// Created by Fabio on 5/02/2017.
//


#include <jni.h>

#include "native-sysfs.h"
#include "native-sysfs-listener-client.h"


extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_exportPin(JNIEnv *env, jobject instance) {

    int fd = GPIOOpenFd(23, OUT);

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

    int fd = GPIOOpenFd(pinNumber, OUT);

    if (fd > 0) {

        if (GPIOWriteFd(fd, HIGH)) {
            for (int i = 0; i < count; i++) {
                GPIOWriteFd(fd, LOW);
                GPIOWriteFd(fd, HIGH);
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

    // TODO

}

