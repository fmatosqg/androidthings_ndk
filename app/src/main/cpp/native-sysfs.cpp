//
// Created by Fabio on 27/01/2017.
//

//Based on http://elinux.org/RPi_GPIO_Code_Samples

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include "native-sysfs.h"
#include "native-sysfs-listener-client.h"

#define BUFFER_MAX 3

int GPIOUnexport(int pin) {
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

    LOGD("Closed pin %d", pin);
    close(fd);
    return (0);
}

/**
 * Returns true if successfull, false otherwise
 */
bool GPIODirection(int pin, int dir) {

#define DIRECTION_MAX 35
    char path[DIRECTION_MAX];
    int fd;
    char out[] = {"out\n"};
    char in[] = {"in\n"};

    char *chDir = NULL;

    if (dir == DIRECTION_OUT) {
        chDir = out;
    }

    if (dir == DIRECTION_IN) {
        chDir = in;
    }

    if (chDir == NULL) {
        return false;
    }
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        LOGE("Failed to open gpio direction for writing! %s\n", path);
        return false;
    }


    if (-1 == write(fd, chDir, 4)) {
        LOGE("Failed to set direction!\n");
        return false;
    }

    close(fd);
    return true;
}

int ffGPIORead(int pin) {
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


int GPIOReadFd(int fd) {

    char value_str[3];

    int result = read(fd, value_str, 3);

    if (result == -1) {
        LOGE("Failed to read value!\n");
        return (-1);
    }

    if ( result > 0 ) {
        LOGE("Read value is %s", value_str);
    } else {
        LOGD("read 0 bytes");
    }

    return 1;
}

int GPIOOpenFd(int pin) {
    char path[VALUE_MAX];
    int fd = 0;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDWR);
    if (-1 == fd) {
        LOGE("Failed to open gpio value for writing!\n");
        return (-1);
    }

    return fd;
}

int GPIOCloseFd(int pin, int fd) {
    GPIOUnexport(pin);

    if (fd > 0) {
        return close(fd);
    } else {
        return -1;
    }
}

/**
 * Returns true if ok
 */
bool GPIOWriteFd(int fd, int value) {
    static const char s_values_str[] = "01";

    if (1 != write(fd, &s_values_str[WRITE_LOW == value ? 0 : 1], 1)) {
        LOGE("Failed to write value!\n");
        return false;
    }

    return true;
}

/**
 * Returns fd if successfull, value < 0 if any problem is found
 */

#define ERROR_UNNKNOWN -1
#define ERROR_EXPORT -2
#define ERROR_DIRECTION -3
#define ERROR_GET_FD -4
#define ERROR_WRITE -5
#define ERROR_READ -6

int GPIOOpenFd(int pin, int dir) {

    int returnValue = ERROR_UNNKNOWN;
    int fd = 0;

    if (giveWritePermission(pin)) {

        if (GPIODirection(pin, dir)) {
            fd = GPIOOpenFd(pin);

            returnValue = fd;
            if (fd == -1) {
                returnValue = ERROR_GET_FD;
            }
        } else {
            returnValue = ERROR_DIRECTION;
        }
    } else {
        returnValue = ERROR_EXPORT;
    }

    return returnValue;

}

int GPIOSetEdge(unsigned int gpio, char *edge)
{
    int fd, len;
    char buf[VALUE_MAX];

    len = snprintf(buf, sizeof(buf), "/sys/class/gpio/" "gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-edge");
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);
    close(fd);
    return 0;
}