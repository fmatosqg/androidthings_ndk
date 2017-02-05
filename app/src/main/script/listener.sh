#!/bin/bash
# upload to android and run as root


path=/storage/emulated/0/tmp
path=/data/data/com.amazingapps.sample.thingssample
pipe=$path/gpio_export_pipe

gpioPath=/sys/class/gpio

if ! [ -d $path ]
then
    mkdir -p "$path"
fi

trap "rm -f $pipe" EXIT

if [[ ! -p $pipe ]]; then
    mknod $pipe p
fi

chmod 777 $pipe

echo "Created pipe on $pipe, running as $(whoami)"

function configurePin () {
    pin=$1

    echo "Got pin $pin, running as $(whoami)"

    chmod a+w "$gpioPath/export"
    chmod a+w "$gpioPath/unexport"

    echo $pin > "$gpioPath/export"

    chmod a+w "$gpioPath/gpio${pin}/direction"
    chmod a+w "$gpioPath/gpio${pin}/edge"
    chmod a+w "$gpioPath/gpio${pin}/value"

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