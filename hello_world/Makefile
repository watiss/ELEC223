CC          = arm-none-eabi-gcc
CFLAGS      = -Wall -Werror -Wextra -g -O1 -std=gnu99 -nostdlib
TARGET_ARCH = -mcpu=arm7tdmi
AS          = arm-none-eabi-as 
ASFLAGS     = -g
TARGET_MACH = -mcpu=arm7tdmi
LDFLAGS     = -T ldscript

OBJS   = hello2.o my_crt0.o serial.o init.o
OUTPUT = hello2
##############################################

.PHONY: all clean

all: $(OUTPUT).elf $(OUTPUT).lst $(OUTPUT).bin

hello2.o: serial.h
serial.o: serial.h

$(OUTPUT).elf: $(OBJS) ldscript
	arm-none-eabi-ld $(LDFLAGS) $(OBJS) -o $@ 

$(OUTPUT).lst: $(OUTPUT).elf
	arm-none-eabi-objdump -S $< > $@

$(OUTPUT).bin: $(OUTPUT).elf
	arm-none-eabi-objcopy -O binary $< $@

clean: 
	rm -f *~
	rm -f $(OBJS)
	rm -f $(OUTPUT).elf
	rm -f $(OUTPUT).lst
	rm -f $(OUTPUT).bin