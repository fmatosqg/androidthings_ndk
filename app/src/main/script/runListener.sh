#!/usr/bin/env bash
# run from laptop, from project base dir
# Copies file into Android device and runs it

device=Android.local
listenerFile=listener.sh
devicePath=/storage/self/primary/tmp5
#devicePath=/data/data/com.amazingapps.sample.thingssample
laptoptPath=app/src/main/script


userName=root

adb -s $device shell "mkdir -p $devicePath"
adb -s $device push "$laptoptPath/$listenerFile" $devicePath
#adb shell "su $userName cp /storage/emulated/0/tmp/listener.sh $devicePath"
#adb -s $device shell "su u0_a28 \"ls /data/data/com.amazingapps.sample.thingssample/listener.sh\""
#adb -s $device shell "su u0_a28 source $devicePath/$listenerFile"

adb shell "su $userName cat  $devicePath/listener.sh | su $userName " # this is absolutely necessary in order to open the pipe from NDK. But then the script won't be able to su root and change permissions

echo "Listener exit"

