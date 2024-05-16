// Implement PCA9505 functionality

#include <SoftI2C.h>
#include "pca9505.h"

#define NPORTS                  5

#define PCA9505_REG_MSK         0x20
#define PCA9505_REG_PI          0x10
#define PCA9505_REG_IOC         0x18
#define PCA9505_REG_IP          0x00

#define PCA9505_CMD_AI_ON       0x80
#define PCA9505_CMD_AI_OFF      0x00

typedef struct {
    uint8_t ports[NPORTS];
} io_ports_t;

static void set_io_interrupt(const uint8_t addr, const io_ports_t *const io);
static void set_io_polarity(const uint8_t addr, const io_ports_t *const io);
static void set_io_mode(const uint8_t addr, io_ports_t io);
static void send_io_data(const uint8_t addr, const uint8_t reg, const io_ports_t *const io);
static uint8_t recv_port_data(const uint8_t addr, const uint8_t reg, const uint8_t port);
static inline uint8_t get_port(const uint8_t pin);
static inline uint8_t get_bit(const uint8_t pin);

void gpio_init(const uint8_t addr, const uint8_t scl, const uint8_t sda) {
    scl_pin = scl;
    sda_pin = sda;
    I2CInit();

    const io_ports_t interrupt_cfg = { { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
    const io_ports_t pol_mode_cfg = { { 0 } };
    set_io_interrupt(addr, &interrupt_cfg);
    set_io_polarity(addr, &pol_mode_cfg);
    set_io_mode(addr, pol_mode_cfg);
}

uint8_t gpio_digital_read(const uint8_t addr, const uint8_t pin) {
    return recv_port_data(addr, PCA9505_REG_IP, get_port(pin)) & (1 << get_bit(pin)) ? 0 : 1;
}

static void set_io_interrupt(const uint8_t addr, const io_ports_t *const io) {
    send_io_data(addr, PCA9505_REG_MSK, io);
}

static void set_io_polarity(const uint8_t addr, const io_ports_t *const io) {
    send_io_data(addr, PCA9505_REG_PI, io);
}

static void set_io_mode(const uint8_t addr, io_ports_t io) {
    for (int i = 0; i < NPORTS; i++) {
        io.ports[i] = ~io.ports[i];
    }
    send_io_data(addr, PCA9505_REG_IOC, &io);
}

static void send_io_data(const uint8_t addr, const uint8_t reg, const io_ports_t *const io) {
    I2CStart();
    I2CSend(addr << 1);
    I2CSend(reg | PCA9505_CMD_AI_ON);
    for (int i = 0; i < NPORTS; i++) {
        I2CSend(io->ports[i]);
    }
    I2CStop();
}

static uint8_t recv_port_data(const uint8_t addr, const uint8_t reg, const uint8_t port) {
    I2CStart();
    I2CSend(addr << 1);
    I2CSend((reg + (port % 5)) | PCA9505_CMD_AI_OFF);
    I2CRestart();
    I2CSend(addr << 1 | 0x01);
    const uint8_t data = I2CRead();
    I2CStop();
    return data;
}

static uint8_t inline get_port(const uint8_t pin) {
    return pin / 8;
}

static inline uint8_t get_bit(const uint8_t pin) {
    return pin % 8;
}

