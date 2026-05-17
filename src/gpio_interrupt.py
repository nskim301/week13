import os
os.system("sudo pigpiod")

import time
import sys
import pigpio

PIN_BTN  = 14
PIN_LEDR = 16
PIN_LEDG = 20
PIN_LEDB = 21

LOOP_PERIOD_MS = 2000

led_color = 0
last_tick = 0

def myISR(gpio, level, tick):
    global led_color, last_tick

    if level != 0:
        return

    if pigpio.tickDiff(last_tick, tick) < 200_000:
        return
    last_tick = tick

    btn_state = pi.read(PIN_BTN)

    if btn_state == 0:
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

    cb = pi.callback(PIN_BTN, pigpio.FALLING_EDGE, myISR)

    print("!Interrupt!")
    count = 0
    try:
        while True:
            start = time.time()
            print(f"Current seconds: {count:4d} [s]")
            count += 2
            end = time.time()
            time.sleep((LOOP_PERIOD_MS/1000) - (end - start))
    finally:
        cb.cancel()
        pi.stop()
        os.system("sudo killall pigpiod")

