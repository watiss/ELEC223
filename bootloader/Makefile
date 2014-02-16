CC          = arm-none-eabi-gcc
CFLAGS      = -Wall -Werror -Wextra -g -O1 -std=gnu99 -nostdlib
TARGET_ARCH = -mcpu=arm7tdmi
AS          = arm-none-eabi-as 
ASFLAGS     = -g
TARGET_MACH = -mcpu=arm7tdmi
LDFLAGS     = -T ldscript

OBJS        = bootloader2.o bl_commands.o bl_serial.o\
              bl_timer.o bl_utilities.o my_crt0.o init.o
OUTPUT      = bootloader2
################################################################

.PHONY: all clean

all: $(OUTPUT).elf $(OUTPUT).lst $(OUTPUT).bin

bootloader2.o  : bl_commands.h bl_serial.h bl_utilities.h
bl_serial.o    : bl_serial.h bl_timer.h
bl_commands.o  : bl_commands.h bl_serial.h bl_utilities.h
bl_timer.o     : bl_timer.h
bl_utilities.o : bl_utilities.h

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
