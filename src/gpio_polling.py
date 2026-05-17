import os
os.system("sudo pigpiod")

import pigpio
import time
import sys

PIN_BTN  = 14
PIN_LEDR = 16
PIN_LEDG = 20
PIN_LEDB = 21

LOOP_PERIOD_MS = 2000 

led_color = 0

def change_color(pi):
    global led_color

    ################ Write Codes From Here ################
    # Change colors
    #######################################################


if __name__ == "__main__":
    pi = pigpio.pi()
    if not pi.connected:
        print("pigpio demon error!", file=sys.stderr)
        sys.exit(1)

    pi.set_mode(PIN_BTN,  pigpio.INPUT)
    pi.set_pull_up_down(PIN_BTN, pigpio.PUD_UP)

    pi.set_mode(PIN_LEDR, pigpio.OUTPUT)
    pi.set_mode(PIN_LEDG, pigpio.OUTPUT)
    pi.set_mode(PIN_LEDB, pigpio.OUTPUT)

    pi.write(PIN_LEDR, 1)
    pi.write(PIN_LEDG, 1)
    pi.write(PIN_LEDB, 1)

    print("!Polling!")
    count = 0
    try:
        while True:
            start = time.time()
            btn = pi.read(PIN_BTN)

            print(f"Current seconds: {count:4d} [s]")
            count += 2

            if btn == 0:
                led_state = change_color(pi)

            end = time.time()
            time.sleep((LOOP_PERIOD_MS/1000) - (end - start))
    finally:
        pi.stop()
        os.system("sudo killall pigpiod")
