//
// Created by Fabio on 4/02/2017.
//

#ifndef THINGSSAMPLE_NATIVE_SYSFS_H
#define THINGSSAMPLE_NATIVE_SYSFS_H


#define  LOG_TAG    "Native sysfs"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#define DIRECTION_IN  0
#define DIRECTION_OUT 1

#define WRITE_HIGH 1
#define WRITE_LOW 0

#define EDGE_RISING "rising"
#define EDGE_BOTH "both"
#define EDGE_FALLING "falling"


// fine grain functions
int GPIOOpenFd(int pin, int dir);

int GPIOCloseFd(int pin, int fd);

bool GPIOWriteFd(int fd, int value);

int GPIOReadFd(int fd);
int GPIOSetEdge(unsigned int gpio, char *edge);

#endif //THINGSSAMPLE_NATIVE_SYSFS_H
