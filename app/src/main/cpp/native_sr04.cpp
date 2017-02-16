//
// Created by Fabio on 16/02/2017.
//



#include <jni.h>
#include <pthread.h>
#include <android/log.h>
#include <unistd.h>
#include <asm/poll.h>
#include <poll.h>
#include "native-sysfs.h"

float doAll(int pinTrigger, int pinEcho);

extern "C" jfloat
Java_com_amazingapps_sample_thingssample_ndk_NativeHelper_sr04Distance(JNIEnv *env,
                                                                       jobject instance,
                                                                       jint triggerPin,
                                                                       jint echoPin) {


    return doAll(triggerPin, echoPin);

}


timespec timeTrigger;
timespec timeEcho;
long elapsedNs;

bool isInit = false;
float sr04Time = -11.1f;

// marks the start of event
void ticc() {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeTrigger);
}

// marks the end of event, returns nanoseconds elapsed
long tocc(char *msg) {

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timeEcho);

    long elapsedSec = timeEcho.tv_sec - timeTrigger.tv_sec;
    elapsedNs = timeEcho.tv_nsec - timeTrigger.tv_nsec;
    elapsedNs += elapsedSec * 1000 * 1000 * 1000;

    LOGE(msg, elapsedNs);

    float kHz = 1000.0f * 1000.0f / (float) elapsedNs;
//    LOGE("Equivalent to %3.2f kHz", kHz);

    return elapsedNs;
}


void nsleepp(int nanoseconds) {

    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = nanoseconds;

    nanosleep(&ts, NULL);
}


#define MAX_BUF 64


int triggerFd;
int echoFd;

bool openPins(int pinTrigger, int pinEcho) {

    triggerFd = GPIOOpenFd(pinTrigger, DIRECTION_OUT);

    if (triggerFd == -1) {
        LOGE("Error opening write pin %d", pinTrigger);
        return false;
    }

    echoFd = GPIOOpenFd(pinEcho, DIRECTION_IN);
    if (echoFd == -1) {
        LOGE("Error opening read %d", pinEcho);
        return false;
    }

    GPIOSetEdge(pinEcho, EDGE_BOTH);

    return true;
}


bool sendPulse() {

    LOGE("Send pulse");
    GPIOWriteFd(triggerFd, WRITE_HIGH);
    nsleepp(50 * 1000);
    GPIOWriteFd(triggerFd, WRITE_LOW);

    return true;
}

struct pollfd fdset[1];
char *buf[MAX_BUF];

void readEcho() {


    int nfds = 1;

    int timeout = 500;

    int failedReads = 0;

    fdset[0].fd = echoFd;
    fdset[0].events = POLLPRI;

    int rc = poll(fdset, nfds, timeout);

    if (rc < 0) {
        LOGE("\npoll() failed!\n");
        return;
    }

    if (rc == 0) {
        failedReads++;
    }

    if (fdset[0].revents & POLLPRI) {
        lseek(fdset[0].fd, 0, SEEK_SET);
        int len = read(fdset[0].fd, buf, MAX_BUF);

        if (len != 1) {
            LOGD("BUF sz == %d != 1%s", len, buf);
        }
        sr04Time -= 1.0f;
        failedReads = 0;

    }

}

float doAll(int pinTrigger, int pinEcho) {


    int *pin = new int;
    *pin = pinEcho;

    if (!isInit) {
        if (openPins(pinTrigger, pinEcho)) {
            isInit = true;
        }
    }

    if (isInit) {
        readEcho(); // this should timeout
        sendPulse();
        readEcho();
        ticc();
        readEcho();
        float elapsed = tocc("Time %d ns");

        float cm = (elapsed / 2.0f) / 29.1f / 1000.0f;

        LOGD("measure %3.2f cm", cm);
    }


    return sr04Time;
}

