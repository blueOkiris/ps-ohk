// Entry point for Keyboard

#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include <USBHIDKeyboard.h>
#include "pca9505.h"

#define IOEXP0_ADDR     0x20
#define SCL_PIN         30
#define SDA_PIN         31

void setup(void) {
    USBInit();
    gpio_init(IOEXP0_ADDR, SCL_PIN, SDA_PIN);
}

void loop(void) {
    if (gpio_digital_read(IOEXP0_ADDR, 0)) {
        Keyboard_write('B');
    }
}

