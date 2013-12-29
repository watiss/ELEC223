LD = arm-none-eabi-ld
AS = arm-none-eabi-as
LDFLAGS = -Ttext 0x0c200000
ASFLAGS = -g -mcpu=arm7tdmi

all:led.x

led.x:start.o led.o
	$(LD) $(LDFLAGS)  $^ -o $@
%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f *.o *.x
