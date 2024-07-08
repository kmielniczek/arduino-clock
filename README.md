# Arduino clock :alarm_clock:

This project is a simple clock that displays date and time,
and allows user to modify them with buttons.

It's not very accurate tho, because it measures time using arduino crystal oscillator
instead of some proper RTC (but it should be fairly easy to adapt it).

## Required components

- Arduino UNO
- LCD display (Hitachi HD44780 or a compatible chipset)
- Some buttons

## Instruction

As of now, the only instruction is the source code.
The [arduino-clock.ino](./arduino-clock/arduino-clock.ino) sketch file
has `#define` directives that describes how to connect things (you can also change it).

## Afterwords

It is a direct continuation of my code for the final exam
of measurement and control systems class.

Initially it was written for ATMega16 microcontroller,
but later ported to ATMega328p to work with **Arduino UNO.**

---

This readme will be *hopefully* completed at some point...

### License

License? What is a license :sweat_smile:

But yes, you can use it if you want :grin: