# Author: hyunsungkim (hyunsungkim@postech.ac.kr)
# Last modified: 2021-03-09

gpio: gpio.o helper.o
	gcc -o prog.out gpio.o helper.o -lpigpio
	rm -f *.o
gpio_polling: gpio_polling.o helper.o
	gcc -o prog.out gpio_polling.o helper.o -lpigpio
	rm -f *.o
gpio_interrupt: gpio_interrupt.o helper.o
	gcc -o prog.out gpio_interrupt.o helper.o -lpigpio
	rm -f *.o
timer_interrupt: timer_interrupt.o helper.o
	gcc -o prog.out timer_interrupt.o helper.o -lpigpio
	rm -f *.o
timer_interrupt_two: timer_interrupt_two.o helper.o
	gcc -o prog.out timer_interrupt_two.o helper.o -lpigpio
	rm -f *.o
project: project.o helper.o
	gcc -o prog.out project.o helper.o -lpigpio
	rm -f *.o

reset: reset.o helper.o
	gcc -o prog.out reset.o helper.o -lpigpio
	rm -f *.o 

gpio_write: gpio_write.c
	gcc -o prog.out gpio_write.c helper.c -lpigpio
gpio_read: gpio_read.c
	gcc -o prog.out gpio_read.c helper.c -lpigpio
gpio_servo: gpio_servo.c
	gcc -o prog.out gpio_servo.c helper.c -lpigpio

gpio.o: gpio.c
	gcc -c gpio.c
gpio_polling.o: gpio_polling.c
	gcc -c gpio_polling.c
gpio_interrupt.o: gpio_interrupt.c
	gcc -c gpio_interrupt.c
timer_interrupt.o: timer_interrupt.c
	gcc -c timer_interrupt.c
timer_interrupt_two.o: timer_interrupt_two.c
	gcc -c timer_interrupt_two.c
project.o: project.c
	gcc -c project.c

helper.o: helper.c
	gcc -c helper.c
reset.o: reset.c
	gcc -c reset.c


clean:
	rm -f *.o *.out
