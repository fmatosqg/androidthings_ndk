#!/usr/bin/env bash
# run from laptop, from project base dir
# Copies file into Android device and runs it

device=Android.local
listenerFile=listener.sh
devicePath=/storage/self/primary/tmp
laptoptPath=app/src/main/script

adb -s $device shell "mkdir -p $devicePath"
adb -s $device push "$laptoptPath/$listenerFile" $devicePath
adb shell "su u0_a28 cp /storage/emulated/0/tmp/listener.sh /data/data/com.amazingapps.sample.thingssample"
#adb -s $device shell "su u0_a28 \"ls /data/data/com.amazingapps.sample.thingssample/listener.sh\""
#adb -s $device shell "su u0_a28 source $devicePath/$listenerFile"
adb shell "su u0_a28 cat  /data/data/com.amazingapps.sample.thingssample/listener.sh | su u0_a28 " # this is absolutely necessary in order to open the pipe from NDK. But then the script won't be able to su root and change permissions

echo "Listener exit"

