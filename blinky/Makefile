TMPHEX = /tmp/temphex-$(USER)

all: blinky

clean:
	bjam --clean-all

blinky:
	bjam release

install: blinky
	avr-objcopy -O ihex -R .eeprom dist/blinky ${TMPHEX}
	avrdude -p m328p -P /dev/ttyACM0 -U flash:w:${TMPHEX} -c arduino -V	
