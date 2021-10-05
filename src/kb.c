#include "kb.h"

#include "port.h"
#include "int.h"
#include "sys.h"
#include "key.h"
#include "ps2.h"

const char CHARMAP[CHAR_MAP_SIZE] = {
//  00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
     0 ,  0 , '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',  0 ,'\t', // 00
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0 ,  0 , 'a', 's', // 10
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`',  0 ,'\\', 'z', 'x', 'c', 'v', // 20
    'b', 'n', 'm', ',', '.', '/',  0 , '*',  0 , ' ',  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 30
     0,   0 ,  0 ,   0,  0 ,  0 ,  0 , '7', '8', '9', '-', '4', '5', '6', '+', '1', // 40
    '2', '3', '0', '.',  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 50
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 60
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 70
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 80
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 90
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // A0
     0 ,  0 ,  0 ,  0 ,  0 , '/',  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0   // B0
};

const char SHIFTED_CHARMAP[CHAR_MAP_SIZE] = {
//  00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F
     0 ,  0 , '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',  0 ,'\t', // 00
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',  0 ,  0 , 'A', 'S', // 10
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',  0 , '|', 'Z', 'X', 'C', 'V', // 20
    'B', 'N', 'M', '<', '>', '?',  0 , '*',  0 , ' ',  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 30
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , '7', '8', '9', '-', '4', '5', '6', '+', '1', // 40
    '2', '3', '0', '.',  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 50
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 60
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 70
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 80
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // 90
     0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 , // A0
     0 ,  0 ,  0 ,  0 ,  0 , '/',  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0   // B0
};

bool shifted = false;
bool caps = false;

kbkey keybuf = { };
bool dblsc = false;
volatile bool newsc = false;

void ISR kbisr(intf* ifr) {
    uint8 sc = inb(PS2CTRL_DATAPORT);

    if(sc == KB_DOUBLE_SC) {
        dblsc = true;

        endpic();
        return;
    }

    keybuf.sc = sc;

    if(keybuf.sc & 0x80) {
        keybuf.sc &= 0x7F;
        keybuf.ev = release;
    } else {
        keybuf.ev = press;
    }

    if(dblsc) {
        keybuf.sc += KB_DOUBLE_INC;
        dblsc = false;
    }

    if(keybuf.sc < CHAR_MAP_SIZE) {
        keybuf.ch = (shifted ^ caps? SHIFTED_CHARMAP : CHARMAP)[keybuf.sc];
    }

    if(keybuf.sc == KB_LEFT_SHIFT || keybuf.sc == KB_RIGHT_SHIFT) {
        shifted = keybuf.ev == press;
    } else if(keybuf.sc == KB_CAPSLOCK && keybuf.ev == release) {
        caps = !caps;
    }

    newsc = true;

    endpic();
}

void initkb() {
    regint(kbisr, 33);
}

kbkey getkey() {
    while(!newsc) {
        hlt();
    }

    newsc = false;
    return keybuf;
}