#include "helper.h"


/**
 * Returns elapsed time from when the program started, in milliseconds
 *
 * @return Elapsed time from when the program started, in milliseconds
 */
unsigned long millis()
{
    int secs, mics;
    unsigned long time_cur;
    if(gpioTime(PI_TIME_RELATIVE, &secs, &mics) != 0) {
        printf("Invalid GPIO time function. Please contact TA if you get this error\r\n");
        return PI_DEBOUNCE_ERROR;
    }
    time_cur = secs*1000 + mics/1000;
    return time_cur;
}

void sleep_ms(long ms)
{
    int secs, micros;
    if(ms<=0)
        return;
    else if(ms<1)
        gpioDelay((uint32_t) ms*1000);
    else
    {
        secs = (int)(ms/1000);
        micros = (ms%1000)*1000;
        gpioSleep(0, secs, micros);
    }
}


/**
 * Output PWM signal, which can be used to output analog level
 *
 * @params pin GPIO pin to output PWM signal
 * @params level Integer between 0 (= Low) and 255 (= High)
 */
void gpioAnalogWrite(int pin, uint8_t level)
{
    gpioPWM(pin, level);
}


/**
 * Removes input noise (bouncing) of GPIO pins
 *
 * @params pin GPIO pin to receive input signal
 * @note A macro "PI_DEBOUNCE_TIME_MS" must be adjusted properly
 * @return Digital status of the pin, or error codes
 */
int gpioReadDebounce(int pin)
{
    static bool pin_state[40] = {1,};
    static unsigned long pin_toggle_time_ms[40] = {0,};
    bool state_pre, state_cur;
    int i = 0;
    unsigned long interval, time_cur;
    
    if(pin>40 || pin<0) {
        printf("Invalid pin number to be read. Pin number should be 0-40.\r\n");
        return PI_DEBOUNCE_ERROR;
    }

    state_pre = pin_state[pin];
    state_cur = gpioRead(pin);

    if(state_pre != state_cur)
    {
        pin_state[pin] = state_cur;
        time_cur = millis();
        interval = time_cur - pin_toggle_time_ms[pin];
        pin_toggle_time_ms[pin] = time_cur;

        if(interval > PI_DEBOUNCE_TIME_MS) {
            return state_cur;
        }

        return PI_DEBOUNCE_UNSTABLE;
    }

    return PI_DEBOUNCE_UNSTABLE;
}

void insertionSort(int* arr, int n)
{
    int x,j;
    if(n>0) {
        insertionSort(arr, n-1);
        x = *(arr+n);
        for(j=n-1; j>=0&&*(arr+j)>x; j--)
            *(arr+j+1) = *(arr+j);
        *(arr+j+1) = x;
    }
}

void sig_handler(int signum)
{
    gpioTerminate();
    printf("Terminating GPIO..\r\n");
}
