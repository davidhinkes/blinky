TMPHEX = /tmp/temphex-$(USER)

all: blinky

clean:
	bjam --clean-all release

blinky:
	bjam release -d2

install: blinky
	avr-objcopy -j .text -j .data -O ihex dist/blinky ${TMPHEX}
	avrdude -p m328p -P /dev/ttyACM0 -U flash:w:${TMPHEX} -c arduino -e -V	
