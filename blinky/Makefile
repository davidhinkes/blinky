TMPHEX = /tmp/temphex-$(USER)

all: blinky

blinky:
	bjam release

install: blinky
	avr-objcopy -O ihex -R .eeprom bin/gcc-avr/release/blinky ${TMPHEX}
	avrdude -p m328p -P /dev/ttyACM0 -U flash:w:${TMPHEX} -c arduino -V	
