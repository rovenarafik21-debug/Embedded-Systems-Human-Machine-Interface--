# Temperature monitor: Arduino sketch files

All five implementations are .ino files; the four .h interfaces are retained:

- Temperature_Modular.ino: main application, previously main.c.
- dio.ino / dio.h: reused DIO driver, updated for D8/D9/D10.
- LCD.ino / LCD.h: parallel LCD driver.
- ADC.ino / ADC.h: A0 ADC driver.
- LM35.ino / LM35.h: temperature conversion.

Extract into a fresh folder. Open Temperature_Modular.ino inside Temperature_Modular. Keep all nine code/header files together. Select Arduino Uno and its port, then Verify and Upload. Do not add the old .c files: that would define the same functions twice.

The folder-named .ino now contains main(), so the previous empty launcher is replaced. There is no separate main.ino. Arduino combines .ino files and compiles them as C++, even though the code uses C-style constructs. No Arduino APIs or external driver libraries are called; avr/io.h and AVR util/delay.h are used. Timer1 is not configured.

Behaviour and wiring are unchanged. LCD RS=D7, E=D6, D4=D5, D5=D4, D6=D3, D7=D2, RW=GND. LM35 output=A0. Alert LED=D8 through 330 ohms to LED anode, cathode=GND. Buttons D9 and D10 to GND with internal pull-ups. LCD power, contrast and backlight connections remain as previously working.

Defaults: LL=20 C, LH=27 C. D9 increases LH, wrapping from 100 to LL+1. D10 increases LL, wrapping to zero before reaching LH. LED is on below LL or above LH. Reset restores defaults. Use one button at a time, hold about half a second, and release between presses; slow LCD writes can miss short presses.

AVR-G++ 7.3.0 compiled and linked the sources combined in Arduino sketch order, with -mmcu=atmega328p -DF_CPU=16000000UL -Os -std=gnu++11 -Wall -Wextra -Werror. No warnings or errors. Flash: 1726 bytes; static RAM: 36 bytes. This checks AVR C++ compatibility; Arduino IDE preprocessing/Verify and physical upload were not run here.

LM35 conversion assumes AVCC=5000 mV. Showing one decimal place is not a 0.1 C accuracy claim. The single-supply circuit is intended for positive temperatures. It does not detect sensor faults or add alert hysteresis.
