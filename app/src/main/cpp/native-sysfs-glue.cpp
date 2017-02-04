#include <jni.h>
#include <stdio.h>

#include "native-sysfs.h"
#include "native-sysfs-listener-client.h"


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

int openPin(int pinNumber) {

    if (giveWritePermission(pinNumber)) {
        return GPIOExport(pinNumber);
    }
    else {
        LOGE("Listener client failed giving permissions to pin %d",pinNumber);
        return -1;
    }

}

extern "C" jboolean
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_doAll(JNIEnv *env, jobject instance,
                                                                jint pinNumber, jint count,
                                                                jint sleeMs) {


    int rOpen = openPin(pinNumber);

    if (rOpen == 0) {
        int rDirection = GPIODirection(pinNumber, OUT);

        if (rDirection == 0) {

            int rWrite = GPIOWrite(pinNumber, 1);

            if (rWrite == 0) {

                for (int i = 0; i < count; i++) {
                    GPIOWrite(pinNumber, 1);
//        usleep(500 * 1000);
                    GPIOWrite(pinNumber, 0);
//        usleep(500 * 1000);
                }

                return true;
            }
        }
    }

    GPIOUnexport(pinNumber);

    return false;
}
