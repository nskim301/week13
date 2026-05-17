#include <stdio.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_BTN 14
#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21

int main()
{
    int btn_state;
    // GPIO settings
    if(gpioInitialise()<0) {
        printf("Cannot initialize GPIOs\r\n");
        return 1;
    }

    gpioSetMode(PIN_LEDR, PI_OUTPUT);
    gpioSetMode(PIN_LEDG, PI_OUTPUT);
    gpioSetMode(PIN_LEDB, PI_OUTPUT);
    gpioSetMode(PIN_BTN, PI_INPUT);

    gpioSetPullUpDown(PIN_BTN, PI_PUD_UP); // Pull up the button pin
    gpioWrite(PIN_LEDR, PI_LOW);
    gpioWrite(PIN_LEDG, PI_LOW);
    gpioWrite(PIN_LEDB, PI_LOW);


    // Infinite loop
    while(1) {
        btn_state = gpioRead(PIN_BTN);

        if(btn_state == PI_LOW) {
            gpioWrite(PIN_LEDR, PI_HIGH);
            printf("Button is pushed\r\n");
        }
        else {
            gpioWrite(PIN_LEDR, PI_LOW);
            printf("Button is NOT pushed\r\n");
        }

        sleep_ms(500);
    }

    return 1;
}
