#!/usr/bin/env bash
#
# Author: hyunsungkim (hyunsungkim@postech.ac.kr)
# Last modified: 2021-03-09

MODE=$1

if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "ERROR: Run the script with sudo"
    exit
fi

export python=python3
export pip=pip3

if [ $# -ne 1 ]; then
    echo "ERROR: Cannot resolve run mode. Run script must be either 'sudo ./install.sh --install' or 'sudo ./install.sh --debug'"
    exit

elif [ $MODE == "--install" ]; then
    echo "install mode"
    sudo apt update
    sudo apt install -y python-setuptools python3-setuptools vim

    cd /home/pi
    wget https://github.com/joan2937/pigpio/archive/master.zip
    unzip master.zip

    cd pigpio-master
    make
    sudo make install

elif [ $MODE == '--debug' ]; then
    echo "debug mode"
    cd /home/pi/pigpio-master

    gcc --version
    dpkg -l python*-setuptools

    # inspect pigpio
    sudo ./x_pigpio # check C I/F
    sudo pigpiod    # start daemon
    ./x_pigpiod_if2 # check C      I/F to daemon
    ./x_pigpio.py   # check Python I/F to daemon
    ./x_pigs        # check pigs   I/F to daemon
    ./x_pipe        # check pipe   I/F to daemon

    gpio readall
    sudo killall pigpio

#    python --version
#    pip --version
#    python debug.py

fi

