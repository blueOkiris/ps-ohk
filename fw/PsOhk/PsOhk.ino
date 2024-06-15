// Entry point for Keyboard

#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "keyboard.h"

void setup(void) {
    kb_init();
}

void loop(void) {
    kb_update_send();
    delay(1);
}

