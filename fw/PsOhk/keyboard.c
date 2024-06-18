// Implementation of reading keyboard state

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <USBHIDKeyboard.h>
#include "pca9505.h"
#include "keyboard.h"

#define IOEXP0_ADDR     0x20
#define IOEXP1_ADDR     0x21
#define SCL_PIN         30
#define SDA_PIN         32

typedef enum {
    // IO Expander 0
    PSOHK_KEY_ESC =         0,
    PSOHK_KEY_F1 =          1,
    PSOHK_KEY_F2 =          2,
    PSOHK_KEY_F3 =          3,
    PSOHK_KEY_F4 =          4,
    PSOHK_KEY_F5 =          5,
    PSOHK_KEY_F6 =          6,
    PSOHK_KEY_F7 =          7,
    PSOHK_KEY_F8 =          8,
    PSOHK_KEY_F9 =          9,
    PSOHK_KEY_F10 =         10,
    PSOHK_KEY_F11 =         11,
    PSOHK_KEY_F12 =         12,
    PSOHK_KEY_UP =          13,
    PSOHK_KEY_DOWN =        14,
    PSOHK_KEY_LEFT =        15,
    PSOHK_KEY_RIGHT =       16,
    PSOHK_KEY_INS =         17,
    PSOHK_KEY_HOME =        18,
    PSOHK_KEY_PGUP =        19,
    PSOHK_KEY_DELETE =      20,
    PSOHK_KEY_END =         21,
    PSOHK_KEY_PGDOWN =      22,
    PSOHK_KEY_LBRACK =      23,
    PSOHK_KEY_SEMI =        24,
    PSOHK_KEY_COMMA =       25,
    PSOHK_KEY_1 =           26,
    PSOHK_KEY_GRAVE =       27,
    PSOHK_KEY_CAPSLOCK =    28,
    PSOHK_KEY_TAB =         29,
    PSOHK_KEY_SHIFT =       30,
    PSOHK_KEY_RBRACK =      31,
    PSOHK_KEY_APOSTROPHE =  32,
    PSOHK_KEY_PERIOD =      33,
    PSOHK_KEY_2 =           34,
    PSOHK_KEY_W =           35,
    PSOHK_KEY_H =           36,
    PSOHK_KEY_3 =           37,
    PSOHK_KEY_X =           38,
    PSOHK_KEY_K =           39,

    // IO Expander 2
    PSOHK_KEY_G =           40,
    PSOHK_KEY_L =           41,
    PSOHK_KEY_R =           42,
    PSOHK_KEY_4 =           43,
    PSOHK_KEY_J =           44,
    PSOHK_KEY_D =           45,
    PSOHK_KEY_T =           46,
    PSOHK_KEY_F =           47,
    PSOHK_KEY_V =           48,
    PSOHK_KEY_SLASH =       49,
    PSOHK_KEY_5 =           50,
    PSOHK_KEY_M =           51,
    PSOHK_KEY_N =           52,
    PSOHK_KEY_P =           53,
    PSOHK_KEY_B =           54,
    PSOHK_KEY_C =           55,
    PSOHK_KEY_S =           56,
    PSOHK_KEY_Z =           57,
    PSOHK_KEY_BACKSLASH =   58,
    PSOHK_KEY_7 =           59,
    PSOHK_KEY_A =           60,
    PSOHK_KEY_8 =           61,
    PSOHK_KEY_9 =           62,
    PSOHK_KEY_ALT =         63,
    PSOHK_KEY_Y =           64,
    PSOHK_KEY_E =           65,
    PSOHK_KEY_I =           66,
    PSOHK_KEY_0 =           67,
    PSOHK_KEY_WIN =         68,
    PSOHK_KEY_CTRL =        69,
    PSOHK_KEY_SPACE =       70,
    PSOHK_KEY_O =           71,
    PSOHK_KEY_U =           72,
    PSOHK_KEY_RET =         73,
    PSOHK_KEY_DASH =        74,
    PSOHK_KEY_EQ =          75,
    PSOHK_KEY_Q =           76,
    PSOHK_KEY_6 =           77,
    PSOHK_KEY_BACKSPACE =   78,
    PSOHK_UNUSED_1,

    PSOHK_NUM_KEYS
} key_t;

typedef struct {
    bool pressed;
    bool just_changed;
} key_state_t;

// Map our IO to the HID keyboard library's keys
static const uint8_t CHAR_MAP[PSOHK_NUM_KEYS] = {
    KEY_ESC,            KEY_F1,             KEY_F2,             KEY_F3,             KEY_F4,
    KEY_F5,             KEY_F6,             KEY_F7,             KEY_F8,             KEY_F9,
    KEY_F10,            KEY_F11,            KEY_F12,            KEY_UP_ARROW,       KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,     KEY_RIGHT_ARROW,    KEY_INSERT,         KEY_HOME,           KEY_PAGE_UP,
    KEY_DELETE,         KEY_END,            KEY_PAGE_DOWN,      '[',                ';',
    ',',                '1',                '`',                KEY_CAPS_LOCK,      KEY_TAB,
    KEY_LEFT_SHIFT,     ']',                '\'',               '.',                '2',
    'w',                'h',                '3',                'x',                'k',

    'g',                'l',                'r',                '4',                'j',
    'd',                't',                'f',                'v',                '/',
    '5',                'm',                'n',                'p',                'b',
    'c',                's',                'z',                '\\',               '7',
    'a',                '8',                '9',                KEY_LEFT_ALT,       'y',
    'e',                'i',                '0',                KEY_LEFT_GUI,       KEY_LEFT_CTRL,
    ' ',                'o',                'u',                KEY_RETURN,         '-',
    '=',                'q',                '6',                KEY_BACKSPACE,      0
};

// Whether the key is pressed or not
static uint8_t __xdata KEY_STATE[PSOHK_NUM_KEYS / 8] = { 0 };

void kb_init(void) {
    USBInit();
    gpio_init(IOEXP0_ADDR, SCL_PIN, SDA_PIN);
    gpio_init(IOEXP1_ADDR, SCL_PIN, SDA_PIN);
}

void kb_update_send(void) {
    for (int i = 0; i < PSOHK_NUM_KEYS; i++) {
        const uint8_t addr = i < 40 ? IOEXP0_ADDR : IOEXP1_ADDR;
        const uint8_t key = i < 40 ? i : i - 40;
        const bool key_pressed = gpio_digital_read(addr, key);
        const bool key_state = (KEY_STATE[i / 8] >> (i % 8)) & 0x01;

        // Look for state change
        if ((key_pressed && !key_state) || (!key_pressed && key_state)) {
            // If so, update state and send press/release signal
            if (key_pressed) {
                KEY_STATE[i / 8] |= 0x01 << (i % 8);
                Keyboard_press(CHAR_MAP[i]);
            } else {
                KEY_STATE[i / 8] &= (~0x01) << (i % 8);
                Keyboard_release(CHAR_MAP[i]);
            }
        }
    }
}

