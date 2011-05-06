NAME   = lpc2148

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld -v
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
CP      = arm-none-eabi-objcopy
OD		= arm-none-eabi-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  =  -Map main.map -T2138_demo.cmd
CPFLAGS = -O binary
HEXFLAGS = -O ihex
ODFLAGS	= -x --syms

all: test

clean:
	-rm crt.lst crt.o main.o main.out main.map main.dmp main.bin

test: main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp
	@echo "...building hex"
	$(CP) $(HEXFLAGS) main.out main.hex

main.out: crt.o main.o 2138_demo.cmd
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.out  crt.o VIClowlevel.o task.o Led_task.o Motor_task.o main.o 

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst
	
VIClowlevel.o: VIClowlevel.c
	@ echo "..VIC Compiling"
	$(CC) $(CFLAGS) VIClowlevel.c
	
main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	

