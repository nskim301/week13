#include <stdio.h>
#include <pigpio.h>
#include "helper.h"

#define PIN_LEDR 16
#define PIN_LEDG 20
#define PIN_LEDB 21

void switch_led_color(int led_state)
{
    switch(led_state) {
        case 1:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_LOW);
            break; 
        case 2:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;   
        case 3:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;
        case 4:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 5:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 6:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        case 7:
            gpioWrite(PIN_LEDR, PI_HIGH);
            gpioWrite(PIN_LEDG, PI_HIGH);
            gpioWrite(PIN_LEDB, PI_HIGH);
            break;
        default:
            gpioWrite(PIN_LEDR, PI_LOW);
            gpioWrite(PIN_LEDG, PI_LOW);
            gpioWrite(PIN_LEDB, PI_LOW);
            break;
    }
}


int main()
{
    int led_state = 0;
    // GPIO settings
    if(gpioInitialise()<0) {
        printf("Cannot initialize GPIOs\r\n");
        return 1;
    }

    gpioSetMode(PIN_LEDR, PI_OUTPUT);
    gpioSetMode(PIN_LEDG, PI_OUTPUT);
    gpioSetMode(PIN_LEDB, PI_OUTPUT);

    gpioWrite(PIN_LEDR, PI_LOW); // PI_LOW == 0, PI_HIGH == 1
    gpioWrite(PIN_LEDG, PI_LOW);
    gpioWrite(PIN_LEDB, PI_LOW);
    sleep_ms(1000);

    // Infinite loop
    while(1) {
        led_state = (led_state + 1) % 7 + 1;
        switch_led_color(led_state);
        sleep_ms(500);
    }

    return 1;
}
