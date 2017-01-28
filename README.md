# Overview
This app tries to access GPIO through NDK to achieve higher speeds than are possible using Java API.

# Run instructions
Before running app start listening server with

`./app/src/main/scripts/runListener.sh`

Keep it opened. You only need to run it once each time you boot your Android Thing. Tested on Raspberry Pi 3 only. If it stops running start it again at anytime.

To check that it's actually check that `testpipe2` exists:

 `adb -s Android.local shell "ls -l /storage/self/primary/tmp/testpipe2"`

While your program is running you'll see some text on the terminal every time a new pin is opened. Verify that it's working as expected by:

 `adb -s Android.local shell "ls -l /sys/class/gpio/gpio24"`

 and check that  gpio24 folder exists, and both direction and value have read and write permissions for all users (you should see `-rw-rw-rw` next to it).


