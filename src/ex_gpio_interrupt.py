import os
## 백그라운드에서 실행되는 프로그램 -> 사용자가 직접 제어하지 않고, 시스템의 백그라운드에서 실행되면서 특정 기능을 수행하는 프로그램
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

    # 버튼 눌림이 아닌 경우
    if level != 0:
        return
    # 디바운싱 : 마지막 눌림과 200ms 이내면 무시
    if pigpio.tickDiff(last_tick, tick) < 200_000:
        return
    last_tick = tick

    # 버튼 상태 확인 
    btn_state = pi.read(PIN_BTN)

    if btn_state == 0:
        # 색상 순환 (0~7)
        led_color = (led_color + 1) % 8
        # RGB 비트 조합으로 LED 제어 (0이면 ON, 1이면 OFF)
        pi.write(PIN_LEDR, 0 if led_color & 0b100 else 1)
        pi.write(PIN_LEDG, 0 if led_color & 0b010 else 1)
        pi.write(PIN_LEDB, 0 if led_color & 0b001 else 1)
        # 현재 색상 정보 출력
        print(f"[ISR] LED Color changed to {led_color:03b}")


if __name__ == "__main__":
    pi = pigpio.pi()
    if not pi.connected:
        print("pigpio demon error!", file=sys.stderr)
        sys.exit(1)

    # PIN_BTN을 입력 모드로 설정 
    pi.set_mode(PIN_BTN,  pigpio.INPUT)
    # 내부 풀업 저항을 걸어 기본 상태를 HIGH로 설정 -> 버튼을 누르면 LOW
    pi.set_pull_up_down(PIN_BTN, pigpio.PUD_UP)

    pi.set_mode(PIN_LEDR, pigpio.OUTPUT)
    pi.set_mode(PIN_LEDG, pigpio.OUTPUT)
    pi.set_mode(PIN_LEDB, pigpio.OUTPUT)

    # LED 3개를 모두 끔 (1은 꺼진 상태; LOW에 켜지는 회로)
    pi.write(PIN_LEDR, 1)
    pi.write(PIN_LEDG, 1)
    pi.write(PIN_LEDB, 1)

    # 버튼이 눌려서 LOW 신호가 감지되면, myISR 호출
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
