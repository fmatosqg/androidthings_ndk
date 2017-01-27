#include <jni.h>

extern "C"
jstring
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_stringFromJNI(JNIEnv *env,
                                                                        jobject instance) {

    return env->NewStringUTF("hello from helper java class");
}

