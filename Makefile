CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AS=arm-none-eabi-as
OBJCOPY=arm-none-eabi-objcopy
OUTPUT_BINARY_FORMAT=binary
STL=st-flash
MACH=cortex-m4
LIBS= -lgcc
CFLAGS= -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O2 -fno-builtin
LDFLAGS= -nostdlib -T linker.ld -Wl,-Map=app.map 


all: ReadingWriting.o tim2.o oneWire.o delay.o usart.o startup.o main.o regulator.o app.bin app.elf 
startup.o:startup.c tim2.h ReadingWriting.h usart.h
	$(CC) $(CFLAGS) -c -o startup.o startup.c
ReadingWriting.o:ReadingWriting.c ReadingWriting.h 
	$(CC) $(CFLAGS) -c -o ReadingWriting.o ReadingWriting.c
delay.o:delay.c delay.h
	$(CC) $(CFLAGS) -c -o delay.o delay.c
tim2.o:tim2.c tim2.h ReadingWriting.h usart.h
	$(CC) $(CFLAGS) -c -o tim2.o tim2.c
usart.o:usart.c usart.h
	$(CC) $(CFLAGS) -c -o usart.o usart.c
oneWire.o:oneWire.c oneWire.h 
	$(CC) $(CFLAGS) -c -o oneWire.o oneWire.c
regulator.o:regulator.c regulator.h
	$(CC) $(CFLAGS) -c -o regulator.o regulator.c 
main.o:main.c main.h
	$(CC) $(CFLAGS) -c -o main.o main.c 
app.elf:ReadingWriting.h delay.h main.h tim2.h regulator.h oneWire.h usart.h startup.o main.o 
	$(CC) $(LDFLAGS) $(CFLAGS) -o app.elf startup.o ReadingWriting.o regulator.o tim2.o delay.o usart.o oneWire.o main.o $(LIBS)
app.bin:app.elf
	$(OBJCOPY) -O binary $^ $@ 

clean:
	rm -rf *.o *.elf app.map *.bin
load:
	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32l4x.cfg

tags:
	ctags *.c *.h
