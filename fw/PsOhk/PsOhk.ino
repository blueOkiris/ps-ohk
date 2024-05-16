// Entry point for Keyboard

#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include <USBHIDKeyboard.h>

void setup(void) {
    USBInit();
}

void loop(void) {
    Keyboard_write('H');
    Keyboard_write('e');
    Keyboard_write('l');
    Keyboard_write('l');
    Keyboard_write('o');
    Keyboard_write(',');
    Keyboard_write(' ');
    Keyboard_write('w');
    Keyboard_write('o');
    Keyboard_write('r');
    Keyboard_write('l');
    Keyboard_write('d');
    Keyboard_write('!');
    Keyboard_write('\n');
    delay(2000);
}

