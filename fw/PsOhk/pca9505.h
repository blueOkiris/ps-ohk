// API for interacting with the 9505 IO expander

#ifndef __PCA9505_H__
#define __PCA9505_H__

void gpio_init(const uint8_t addr, const uint8_t scl, const uint8_t sda);
uint8_t gpio_digital_read(const uint8_t addr, const uint8_t pin);

#endif

