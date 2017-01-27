#include <jni.h>
#include <rpi3/gpio.h>

extern "C"
jstring
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_stringFromJNI(JNIEnv *env,
                                                                        jobject instance) {

//    handle = dlopen("/usr/lib/libusb.so",
//                    RTLD_LAZY);

    return env->NewStringUTF("hello from helper java class");
}

int testLinking() {
    BGpio* gpio = null;

    BGpio_setValue(gpio,null);
}


/**
 * See /system/lib
 * libbrillo-binder.so             libril.so
libbrillo-http.so               librilutils.so
libbrillo-policy.so             librootdev.so
libbrillo-stream.so             librs_jni.so
libbrillo.so

 > grep -inr i2c *
Binary file libs/hw/peripheral_io.rpi3.so matches

 > grep -inr gpio *
Binary file libs/libperipheralman.so matches

git clone https://android.googlesource.com/platform/system/peripheralmanager --> c project

 unit tests in cloned project contain RegisterGpioSysfs reference

 > grep -rni RegisterGpioSysfs  libs/libperipheralman.so

 >  gobjdump libs/libperipheralman.so -T --target=elf32-littlearm  (got it from Amazon debian who autodetected it)
and use -T to show objects defined in this library
 adb shell
 su
 am start -n "com.amazingapps.sample.thingssample/com.amazingapps.sample.thingssample.view.MainActivity" -a android.intent.action.MAIN -c android.intent.category.LAUNCHER -D


 java.lang.UnsatisfiedLinkError: dlopen failed: library "/system/lib/libperipheralman.so" needed or dlopened by "/system/lib/libnativeloader.so" is not accessible for the namespace "classloader-namespace"

 adb -s Android.local push ./app/build/outputs/apk/app-debug.apk  /storage/self/primary/
 adb -s Android.local root
 adb -s Android.local remount
 su
 cp /storage/self/primary/app-debug.apk /system/app
 pm install /system/app/app-debug.apk

 progress:
  android.content.res.Resources$NotFoundException: failed to add asset path /data/app/com.amazingapps.sample.thingssample-1/base.apk

  mkdir /data/app/com.amazingapps.sample.thingssample-1/
  cp com.amazingapps.sample.thingssample-1/base.apk /data/app/com.amazingapps.sample.thingssample-1/

 java.lang.UnsatisfiedLinkError: dalvik.system.PathClassLoader[DexPathList[[zip file "/system/framework/com.google.android.things.jar", zip file "/data/app/com.amazingapps.sample.thingssample-1/base.apk"],nativeLibraryDirectories=[/data/app/com.amazingapps.sample.thingssample-1/lib/arm, /data/app/com.amazingapps.sample.thingssample-1/base.apk!/lib/armeabi-v7a, /system/lib, /vendor/lib]]] couldn't find "libnative-lib.so"

 mkdir -p /data/app/com.amazingapps.sample.thingssample-1/lib/arm
 cp ./com.amazingapps.sample.thingssample-1/lib/arm/libnative-lib.so  /data/app/com.amazingapps.sample.thingssample-1/lib/arm

 mv /data/app/com.amazingapps.sample.thingssample-1/lib/arm/libnative-lib.so  /system/lib

 rpi3:/system/app # ls -lsa /system/lib/libnativeloader.so
72 -rw-r--r-- 1 root root 34448 2016-12-12 21:04 /system/lib/libnativeloader.so
 chmod a+x /system/lib/libnativeloader.so
 chmod a+x /system/lib/libnative-lib.so
 /system/lib/libnative-lib.so

 java.lang.UnsatisfiedLinkError: dlopen failed: library "/system/lib/libnative-lib.so" needed or dlopened by "/system/lib/libnativeloader.so" is not accessible for the namespace "classloader-namespace"


 ----------- could not solve by this method

 http://qiita.com/hidenorly/items/ab1cd6fc5f1c425802e6 -- this page is a gem

 copied /system/framework/com.google.android.things.jar and /system/lib/libandroidthings_jni.so for examining

 can load libandroidthings_jni library from APK without a problem

 > jar xf com.google.android.things.jar
 gives a dex file
 > zip -r FILENAME.apk classes.dex
 > dex2jar-2.0/d2j-dex2jar.sh -f -o classes.jar FILENAME.apk

 issues with version 37 because last dex2jar only supports version 35
 > git clone git@github.com:pxb1988/dex2jar.git
 > cd ...
 make some edits as per https://github.com/pxb1988/dex2jar/issues/93
 > ./gradlew build
 > cp dex-tools/build/distribution/*tar
 > tar xf ....tar
 > cd ???
 > ./d2j-dex2jar.sh ../../FILENAME.apk
finally get file ./FILENAME-dex2jar.jar


! See also how to preload a library and run a program before other libraries get loaded
 http://www.linuxjournal.com/article/7795

 */
