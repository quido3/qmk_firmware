#!/bin/sh

sleep 10
avrdude -p m32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:../../../../../.build/ronin_default.hex
