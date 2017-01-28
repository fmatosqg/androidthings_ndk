#include <jni.h>
#include <stdio.h>
#include <fcntl.h>


/**
 * Must open named pipe and write the pin number there.
 *
 * That will invoke listener.sh which will give the appropriate permissions
 * running as superuser.
 */
bool giveWritePermission(int pinNumber) {

//    char *myfifo = "/storage/emulated/0/tmp/testpipe2";
    char *myfifo = "/data/data/com.amazingapps.sample.thingssample/testpipe";
    int fd = open(myfifo, O_WRONLY);
    char buffer[10];

    sprintf(buffer,"%d\n",pinNumber);

    if ( fd != -1 ) {
        int rWrite = write(fd,buffer,strlen(buffer));
        int rClose = close(fd);

        return true;
    }

    return false;
}


//void giveWritePermission(int number) {
//
//    char device[100];
//
////    su root chmod a+w direction
//
//    sprintf(device, "/sys/class/gpio/gpio%d/direction", number);
//    int a = execl("/system/xbin/su",
//                  "root",
//                  "/system/bin/chmod",
//                  "a+rw",
//                  device,
//                  (char *) NULL);
//
//    sprintf(device, "/sys/class/gpio/gpio%d/value", number);
//    execl("/system/xbin/su",
//          "root",
//          "/system/bin/chmod",
//          "a+rw",
//          device,
//          (char *) NULL);
//
//    int rSystem = system("su root chmod a+w /sys/class/gpio/gpio24/edge");
//
//    LOGE("System returned %d",rSystem);
//
//    int rSystemTouch = system("/system/bin/date > /storage/self/primary/now ");
//
//    LOGE("System returned %d",rSystem);
//
//}