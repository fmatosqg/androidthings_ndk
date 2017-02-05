//
// Created by Fabio on 9/02/2017.
//

#ifndef ANDROIDTHINGS_NDK_NATIVE_SYSFS_ASYNCHRONOUS_H
#define ANDROIDTHINGS_NDK_NATIVE_SYSFS_ASYNCHRONOUS_H

int startWritingThread(int pinNumberOut);
int startReadingThread(int pinNumberIn);

#endif //ANDROIDTHINGS_NDK_NATIVE_SYSFS_ASYNCHRONOUS_H
