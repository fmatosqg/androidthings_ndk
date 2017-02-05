# Overview
This app tries to access GPIO through NDK to achieve higher speeds than are possible using Java API.

# Run instructions
Before running app start listening server with

`./app/src/main/scripts/runListener.sh`

Keep it opened. You only need to run it once each time you boot your Android Thing. Tested on Raspberry Pi 3 only. If it stops running start it again at anytime.

To check that it's actually check that `gpio_export_pipe` exists:

 `adb -s Android.local shell "ls -l /data/data/com.amazingapps.sample.thingssample/gpio_export_pipe"`

While your program is running you'll see some text on the terminal every time a new pin is opened. Verify that it's working as expected by:

 `adb -s Android.local shell "ls -l /sys/class/gpio/gpio23"`

 and check that  gpio23 folder exists, and both direction and value have read and write permissions for all users (you should see `-rw-rw-rw` next to it).


# Stack Overflow related questions
http://stackoverflow.com/questions/41727580/what-is-android-things-raspberry-pi-gpio-max-frequency/42036540#42036540
