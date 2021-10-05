#include "io.h"

#include "port.h"
#include "kb.h"
#include "color.h"
#include "string.h"
#include "varg.h"
#include "key.h"

scrval globalsv = (scrval) { ' ', VGA_CLR_STANDARD };
scrval* VGA_PTR = (scrval*) VGA_MEM_START;

const cursh CUR_SH_DISABLED = { 0x0, 0x0 };
const cursh CUR_SH_UNDERLINE = { 0xE, 0xF };
const cursh CUR_SH_BOX = { 0x0, 0xF };

void setcurs(cursh state) {
    if(state.ssl == 0 && state.esl == 0) {
        outb(CUR_DATAPORT_1, CUR_COM_STATE_1);
        outb(CUR_DATAPORT_2, 0x20);
        return;
    }

    outb(CUR_DATAPORT_1, CUR_COM_STATE_1);
    outb(CUR_DATAPORT_2, (inb(CUR_DATAPORT_2) & 0xC0) | state.ssl);

    outb(CUR_DATAPORT_1, CUR_COM_STATE_2);
    outb(CUR_DATAPORT_2, (inb(CUR_DATAPORT_2) & 0xE0) | state.esl);
}

void setcurp(uint16 pos) {
    outb(CUR_DATAPORT_1, CUR_COM_POS_1);
    outb(CUR_DATAPORT_2, (pos & 0xFF));
    outb(CUR_DATAPORT_1, CUR_COM_POS_2);
    outb(CUR_DATAPORT_2, (pos >> 8) & 0xFF);

    while(getcurp() >= VGA_SCR_CELLS) {
        movs(1);
    }
}

void addcurp(uint16 add) {
    setcurp(getcurp() + add);
}

uint16 getcurp() {
    uint16 pos = 0;

    outb(CUR_DATAPORT_1, CUR_COM_POS_1);
    pos |= inb(CUR_DATAPORT_2);
    outb(CUR_DATAPORT_1, CUR_COM_POS_2);
    pos |= ((uint16) inb(CUR_DATAPORT_2)) << 8;

    return pos;
}

void setclr(uint8 color) {
    globalsv.clr = color;
}

void clrs() {
    setcurp(0);

    for(uint16 i = 0; i <= VGA_SCR_CELLS; i++) {
        poke(globalsv, i);
    }
}

void movs(uint8 rows) {
    uint16 cells = rows * VGA_SCR_COLS;

    for(uint16 i = 0; i < VGA_SCR_CELLS; i++) {
        poke(peek(i), i - cells);
    }

    for(uint16 i = 0; i < cells; i++) {
        poke(globalsv, VGA_SCR_CELLS - cells + i);
    }

    addcurp(-cells);
}

scrval peek(uint16 pos) {
    return pos < VGA_SCR_CELLS? VGA_PTR[pos] : (scrval) { };
}

void poke(scrval sv, uint16 pos) {
    if(pos < VGA_SCR_CELLS) {
        VGA_PTR[pos] = sv;
    }
}

void putc(char ch) {
    while(true) {
        switch (ch) {
            case '\n': {
                setcurp(xytocur(0, curtoy(getcurp()) + 1));
                break;
            }

            case '\r': {
                setcurp(xytocur(0, curtoy(getcurp())));
                break;
            }

            case '\t': {
                if(curtox(getcurp()) % 4 != 0) {
                    poke(globalsv, getcurp());
                    addcurp(1);
                    continue;
                }

                break;
            }

            case '\b': {
                addcurp(-1);
                poke(globalsv, getcurp());

                break;
            }

            default: {
                poke((scrval) { ch, globalsv.clr }, getcurp());
                addcurp(1);
                break;
            }
        }

        break;
    }
}

void puts(const char* str) {
    sputs(str);
    putc('\n');
}

void sputs(const char* str) {
    for(strsz i = 0; str[i] != 0; i++) {
        putc(str[i]);
    }
}

void printf(const char* format, ...) {
    valist args = vainit(format);

    for(strsz i = 0; format[i] != 0; i++) {
        if(format[i] == '%') {
            i++;

            if(format[i] == 0) {
                putc('%');
                continue;
            }

            switch (format[i]) {
                case 'd': case 'i': {
                    char buf[12];
                    itos(vanext(args, int), buf);
                    sputs(buf);
                    break;
                }

                case 'x': {
                    char buf[12];
                    xtos(vanext(args, int), buf);
                    sputs(buf);
                    break;
                }

                case 's': {
                    sputs(vanext(args, const char*));
                    break;
                }

                case 'c': {
                    putc(vanext(args, int));
                    break;
                }

                case '%':
                    putc('%');
                default: {
                    putc('%');
                    break;
                }
            }
        } else {
            putc(format[i]);
        }
    }
}

char getc() {
    kbkey k;

    while((k = getkey()).ch == 0 || k.ev != press);

    return k.ch;
}

void gets(char* buf) {
    kbkey key;
    strsz i = 0;

    while(!((key = getkey()).sc == KB_ENTER && key.ev == press)) {
        if(key.ev == release)
            continue;

        switch (key.sc) {
            case KB_BACKSPACE: case KB_LEFT: {
                if(i > 0) {
                    putc('\b');
                    i--;
                }

                break;
            }

            case KB_TAB:
                break;

            default: {
                if(key.ch != 0) {
                    buf[i] = key.ch;
                    putc(key.ch);
                    i++;
                }

                break;
            }
        }
    }

    puts("");

    buf[i] = 0;
}