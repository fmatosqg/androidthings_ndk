//
// Created by Fabio on 27/01/2017.
//

//http://elinux.org/RPi_GPIO_Code_Samples

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define  LOG_TAG    "Native sysfs"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static int
GPIOExport(int pin) {
#define BUFFER_MAX 3
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY); // creates dev /sys/class/gpio/gpio23/
    if (-1 == fd) {
        LOGE("Failed to open /sys/class/gpio/export for writing!\n");
        return (-1);
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return (0);
}

static int
GPIOUnexport(int pin) {
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
        LOGE("Failed to open /sys/class/gpio/unexport for writing!\n");
        return (-1);
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    return (0);
}

static int
GPIODirection(int pin, int dir) {
    static const char s_directions_str[] = "in\0out";

#define DIRECTION_MAX 35
    char path[DIRECTION_MAX];
    int fd;
    char out[] = {"out\n"};

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        LOGE("Failed to open gpio direction for writing!\n");
        return (-1);
    }


    if (-1 == write(fd, out, 4)) {
        LOGE("Failed to set direction!\n");
        return (-1);
    }

    close(fd);
    return (0);
}

static int
GPIORead(int pin) {
#define VALUE_MAX 30
    char path[VALUE_MAX];
    char value_str[3];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        LOGE("Failed to open gpio value for reading!\n");
        return (-1);
    }

    if (-1 == read(fd, value_str, 3)) {
        LOGE("Failed to read value!\n");
        return (-1);
    }

    close(fd);

    return (atoi(value_str));
}

static int
GPIOWrite(int pin, int value) {
    static const char s_values_str[] = "01";

    char path[VALUE_MAX];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        LOGE("Failed to open gpio value for writing!\n");
        return (-1);
    }

    if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
        LOGE("Failed to write value!\n");
        return (-1);
    }

    close(fd);
    return (0);
}


