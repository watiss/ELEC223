JPGFILES = $(wildcard *.jpg)
PNGFILES = $(patsubst %.jpg,%.png,$(JPGFILES))

PNGFILES += $(wildcard *.png)
EPSFILES = $(patsubst %.png,%.eps,$(PNGFILES))

.PHONY: all clean 

all: $(EPSFILES)

%.png: %.jpg
	$(shell convert $< $@)
%.eps: %.png
	$(shell convert $< $@)
	@grep '%%Bounding' $@

clean:
	rm -f $(patsubst %.jpg,%.png,$(JPGFILES))
	rm -f $(EPSFILES)