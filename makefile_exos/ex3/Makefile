CFLAGS = -g -Wall
CFILES = $(wildcard *.c)
OFILES = $(patsubst %.c,%.o,$(CFILES))

main: $(OFILES)
clean:
	rm -f $(OFILES)
	rm -f main