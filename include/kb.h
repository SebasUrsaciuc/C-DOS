#pragma once

#include "def.h"

typedef enum { press, release } kb_ev, kb_event;
typedef struct {
    char ch;
    uint16 sc;
    kb_event ev;
} kb_key;

#define KB_CHARMAP_SIZE 0xC0

#define KB_DOUBLE_INC 0x80
#define KB_DOUBLE_SC 0xE0

// ALPHANUMERIC
#define KB_KEY_1 0x02
#define KB_KEY_2 0x03
#define KB_KEY_3 0x04
#define KB_KEY_4 0x05
#define KB_KEY_5 0x06
#define KB_KEY_6 0x07
#define KB_KEY_7 0x08
#define KB_KEY_8 0x09
#define KB_KEY_9 0x0A
#define KB_KEY_0 0x0B

#define KB_KEY_Q 0x10
#define KB_KEY_W 0x11
#define KB_KEY_E 0x12
#define KB_KEY_R 0x13
#define KB_KEY_T 0x14
#define KB_KEY_Y 0x15
#define KB_KEY_U 0x16
#define KB_KEY_I 0x17
#define KB_KEY_O 0x18
#define KB_KEY_P 0x19
#define KB_KEY_A 0x1E
#define KB_KEY_S 0x1F
#define KB_KEY_D 0x20
#define KB_KEY_F 0x21
#define KB_KEY_G 0x22
#define KB_KEY_H 0x23
#define KB_KEY_J 0x24
#define KB_KEY_K 0x25
#define KB_KEY_L 0x26
#define KB_KEY_Z 0x2C
#define KB_KEY_X 0x2D
#define KB_KEY_C 0x2E
#define KB_KEY_V 0x2F
#define KB_KEY_B 0x30
#define KB_KEY_N 0x31
#define KB_KEY_M 0x32

#define KB_KEY_SPACE 0x39

#define KB_KEY_MINUS 0x0C
#define KB_KEY_EQUAL 0x0D
#define KB_KEY_OPEN_BRACKET 0x1A
#define KB_KEY_CLOSED_BRACKET 0x1B
#define KB_KEY_SEMICOLON 0x27
#define KB_KEY_SINGLE_QUOTE 0x28
#define KB_KEY_BACK_TICK 0x29
#define KB_KEY_BACKSLASH 0x2B
#define KB_KEY_COMMA 0x33
#define KB_KEY_PERIOD 0x34
#define KB_KEY_SLASH 0x35

// ALPHANUMERIC FUNC
#define KB_KEY_BACKSPACE 0x0E
#define KB_KEY_TAB 0x0F
#define KB_KEY_ENTER 0x1C
#define KB_KEY_LEFT_CONTROL 0x1D
#define KB_KEY_LEFT_SHIFT 0x2A
#define KB_KEY_RIGHT_SHIFT 0x36
#define KB_KEY_LEFT_ALT 0x38
#define KB_KEY_CAPSLOCK 0x3A

// EDITING FUNC
#define KB_KEY_ESC 0x01

#define KB_KEY_F1 0x3B
#define KB_KEY_F2 0x3C
#define KB_KEY_F3 0x3D
#define KB_KEY_F4 0x3E
#define KB_KEY_F5 0x3F
#define KB_KEY_F6 0x40
#define KB_KEY_F7 0x41
#define KB_KEY_F8 0x42
#define KB_KEY_F9 0x43
#define KB_KEY_F10 0x44
#define KB_KEY_F11 0x57
#define KB_KEY_F12 0x58

#define KB_KEY_SCROLLLOCK 0x46
#define KB_KEY_INSERT (KB_DOUBLE_INC + 0x52)
#define KB_KEY_HOME (KB_DOUBLE_INC + 0x47)
#define KB_KEY_PAGEUP (KB_DOUBLE_INC + 0x7D)
#define KB_KEY_PAGEDOWN (KB_DOUBLE_INC + 0x7A)
#define KB_KEY_DELETE (KB_DOUBLE_INC + 0x53)
#define KB_KEY_END (KB_DOUBLE_INC + 0x4F)

#define KB_KEY_UP (KB_DOUBLE_INC + 0x48)
#define KB_KEY_DOWN (KB_DOUBLE_INC + 0x50)
#define KB_KEY_LEFT (KB_DOUBLE_INC + 0x4B)
#define KB_KEY_RIGHT (KB_DOUBLE_INC + 0x4D)

// NUMPAD FUNC
#define KB_KEY_NUMLOCK 0x45
#define KB_KEY_NUM_SLASH (KB_DOUBLE_INC + 0x35)
#define KB_KEY_NUM_ASTERISK 0x37
#define KB_KEY_NUM_MINUS 0x4A
#define KB_KEY_NUM_PLUS 0x4E
#define KB_KEY_NUM_ENTER (KB_DOUBLE_INC + 0x1C)
#define KB_KEY_NUM_PERIOD 0x53

// NUMPAD
#define KB_KEY_NUM_1 0x4F
#define KB_KEY_NUM_2 0x50
#define KB_KEY_NUM_3 0x51
#define KB_KEY_NUM_4 0x4B
#define KB_KEY_NUM_5 0x4C
#define KB_KEY_NUM_6 0x4D
#define KB_KEY_NUM_7 0x47
#define KB_KEY_NUM_8 0x48
#define KB_KEY_NUM_9 0x49
#define KB_KEY_NUM_0 0x52

extern const char KB_CHARMAP[KB_CHARMAP_SIZE];
extern const char KB_SHIFTED_CHARMAP[KB_CHARMAP_SIZE];

/* Initializes the keyboard. */
void kb_init();

/* Waits for key press and returns it. */
kb_key kb_getKey();