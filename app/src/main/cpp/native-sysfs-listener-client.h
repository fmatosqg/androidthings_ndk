//
// Created by Fabio on 4/02/2017.
//

#ifndef THINGSSAMPLE_NATIVE_SYSFS_LISTENER_CLIENT_H
#define THINGSSAMPLE_NATIVE_SYSFS_LISTENER_CLIENT_H

#include <stdio.h>
#include <fcntl.h>
#include <android/log.h>
#include <jni.h>


extern "C" jboolean
        Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_exportPin(JNIEnv *env, jobject instance);

int openPin(int pinNumber);


extern "C" jboolean
        Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_doAll(JNIEnv *env, jobject instance,
                                                                        jint pinNumber, jint count,
                                                                        jint sleeMs);

bool giveWritePermission(int pinNumber);

#endif //THINGSSAMPLE_NATIVE_SYSFS_LISTENER_CLIENT_H
