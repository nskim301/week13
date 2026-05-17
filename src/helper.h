#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <pigpio.h>

#define PI_DEBOUNCE_ERROR -1
#define PI_DEBOUNCE_UNSTABLE -2
// Adjust PI_DEBOUNCE_TIME_MS to remove button noise.
#define PI_DEBOUNCE_TIME_MS 300

unsigned long millis(void);
void sleep_ms(long ms);
int gpioReadDebounce(int pin);
void insertionSort(int* arr, int n);
void sig_handler(int signum);
void gpioAnalogWrite(int pin, uint8_t level);
