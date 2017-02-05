#include "native-sysfs-listener-client.h"

#define  LOG_TAG    "Native sysfs"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


/**
 * Must open named pipe and write the pin number there.
 *
 * That will invoke listener.sh which will give the appropriate permissions
 * running as superuser.
 */
bool giveWritePermission(int pinNumber) {

    char myfifo[] = "/data/data/com.amazingapps.sample.thingssample/gpio_export_pipe";
    int fd = open(myfifo, O_WRONLY);
    char buffer[10];

    sprintf(buffer, "%d\n", pinNumber);

    if (fd != -1) {

        int rWrite = write(fd, buffer, strlen(buffer));
        int rClose = close(fd);

        int sleepMs = 500;
        usleep(sleepMs * 1000);

        LOGE("Open pin %d, sleep %d ms", pinNumber,
             sleepMs);


        return true;
    }

    LOGE("Failed writing at %s", myfifo);

    return false;
}
