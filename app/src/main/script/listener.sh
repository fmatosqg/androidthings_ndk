#!/bin/bash
# upload to android and run as
# source listener.sh

path=/storage/emulated/0/tmp
#path=/data/data/com.amazingapps.sample.thingssample
pipe=/data/data/com.amazingapps.sample.thingssample/testpipe

gpioPath=/sys/class/gpio/

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mknod $pipe p
fi

echo "Created pipe on $pipe"

function configurePin () {
    pin=$1

    echo "Got pin $pin"

    #su root chmod a+w "$gpioPath/export"
    #su root chmod a+w "$gpioPath/unexport"

    echo $pin > "$gpioPath/export"
    chmod a+w "$gpioPath/gpio${pin}/direction"
    su root chmod a+w "$gpioPath/gpio${pin}/direction"
    su root chmod a+w "$gpioPath/gpio${pin}/value"

}

function listener() {
    echo "Listener starting"

    while true
    do
        if read pin <$pipe; then
            if [[ "pin" == 'quit' ]]; then
                break
            fi
            echo $pin
            configurePin $pin
        fi
    done

    echo "Listener exiting"
}

listener