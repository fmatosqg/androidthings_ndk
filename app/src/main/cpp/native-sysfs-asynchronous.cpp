#include <android/log.h>
//#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <poll.h>

#include "native-sysfs-asynchronous.h"
#include "native-sysfs.h"

void nsleep(int nanoseconds) {

    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = nanoseconds;

    nanosleep(&ts, NULL);
}

/* this function is run by the second thread */
void *writeThread(void *pin) {

    int writePin = *(int *) pin;

    int fd = GPIOOpenFd(writePin, DIRECTION_OUT);

    if (fd == -1) {
        LOGE("Error opening write pin %d", writePin);
        return NULL;
    }

    while (true) {

        GPIOWriteFd(fd, WRITE_HIGH);
        nsleep(500 * 1000 * 1000);
        GPIOWriteFd(fd, WRITE_LOW);
        nsleep(500 * 1000 * 1000);

        LOGD("W %d", writePin);
    }

    GPIOCloseFd(writePin, fd);

    return NULL;

}

int GPIOPollFd(int fd) {

}

#define MAX_BUF 64

void *readThread(void *pin) {

    struct pollfd fdset[1];
    int nfds = 1;
    char *buf[MAX_BUF];

    int readPin = *(int *) pin;

    int fd = GPIOOpenFd(readPin, DIRECTION_IN);
    if (fd == -1) {
        LOGE("Error opening read %d", readPin);
        return NULL;
    }

    int gpio_fd = fd;

    GPIOSetEdge(readPin, EDGE_BOTH);

    int timeout = 3 * 1000;

    while (true) {

        fdset[0].fd = gpio_fd;
        fdset[0].events = POLLPRI;

        int rc = poll(fdset, nfds, timeout);

        if (rc < 0) {
            LOGE("\npoll() failed!\n");
            return NULL;
        }

        if (rc == 0) {
            LOGE(".");
        }

        if (fdset[0].revents & POLLPRI) {
            lseek(fdset[0].fd, 0, SEEK_SET);
            int len = read(fdset[0].fd, buf, MAX_BUF);
            LOGE("poll() GPIO %d interrupt occurred, got value %s", readPin, buf);
        }

        LOGD("R %d", readPin);

    }

    GPIOCloseFd(readPin, fd);

    return NULL;

}


int startWritingThread(int pinNumberOut) {

    int *pin = new int;
    *pin = pinNumberOut;

    LOGE("Write thread sample on pin %d", pinNumberOut);

    pthread_t writeThread_t;

    if (pthread_create(&writeThread_t, NULL, writeThread, pin)) {
        LOGE("Error creating thread");
        return 1;

    }

    return 0;
}

int startReadingThread(int pinNumberIn) {
    LOGE("Read thread sample");

    int *pin = new int;
    *pin = pinNumberIn;

    pthread_t readThread_t;

    if (pthread_create(&readThread_t, NULL, readThread, pin)) {
        LOGE("Error creating thread");
        return 1;

    }

    return 0;
}