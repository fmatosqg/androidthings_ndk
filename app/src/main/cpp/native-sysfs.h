//
// Created by Fabio on 4/02/2017.
//

#ifndef THINGSSAMPLE_NATIVE_SYSFS_H
#define THINGSSAMPLE_NATIVE_SYSFS_H


#define  LOG_TAG    "Native sysfs"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1


//bool GPIODirection(int pin, int dir);

//int GPIORead(int pin);

//int GPIOWrite(int pin, int value);


// fine grain functions
//int GPIOOpenFd(int pin);

int GPIOOpenFd(int pin, int dir);

int GPIOCloseFd(int pin, int fd);

bool GPIOWriteFd(int fd, int value);


#endif //THINGSSAMPLE_NATIVE_SYSFS_H
