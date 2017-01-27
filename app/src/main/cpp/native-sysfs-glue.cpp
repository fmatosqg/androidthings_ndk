#include <jni.h>
#include <stdio.h>

#include "native-sysfs.cpp"

extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_exportPin(JNIEnv *env, jobject instance) {


    printf("AAAAAA\n");

    int r = GPIOExport(23);

    GPIOUnexport(23);
    if (r == 0) {
        return true;
    } else {
        return false;
    }
}

extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_doAll(JNIEnv *env, jobject instance,
                                                                jint pinnnn, jint count,
                                                                jint sleeMs) {

    int pinNumber = 24;

    int r = GPIOExport(pinNumber);

    GPIODirection(pinNumber, OUT);

//    for ( int i = 0; i < count ; i++) {
//        GPIOWrite(pinNumber,1);
////        usleep(500 * 1000);
//        GPIOWrite(pinNumber,0);
////        usleep(500 * 1000);
//    }

//    GPIOUnexport(pinNumber);
}
