#include "misc/io.h"

#include "drv/sound.h"
#include "drv/vga.h"
#include "drv/kb.h"
#include "misc/string.h"
#include "varg.h"

const vga_char empty = (vga_char) { ' ', VGA_CLR_NULL }; 

void io_putChar(char ch) {
    while(true) {
        switch (ch) {
            case '\n': {
                vga_setPos(vga_posFromXY(0, vga_posToY(vga_getPos()) + 1));
                break;
            }

            case '\r': {
                vga_getPos(vga_posFromXY(0, vga_posToY(vga_getPos())));
                break;
            }

            case '\t': {
                if(vga_posToX(vga_getPos()) % 4 != 0) {
                    vga_poke(empty, vga_getPos());
                    vga_incPos(1);
                    continue;
                }

                break;
            }

            case '\b': {
                vga_incPos(-1);
                vga_poke(empty, vga_getPos());

                break;
            }

            case '\a': {
                snd_beep(800, 200);

                break;
            }

            default: {
                vga_poke((vga_char) { ch, VGA_CLR_NULL }, vga_getPos());
                vga_incPos(1);
                
                break;
            }
        }

        break;
    }
}

void io_println(const char* str) {
    io_print(str);
    io_putChar('\n');
}

void io_print(const char* str) {
    for(str_sz i = 0; str[i] != 0; i++) {
        io_putChar(str[i]);
    }
}

void io_printf(const char* format, ...) {
    va_list args = va_init(format);

    for(str_sz i = 0; format[i] != 0; i++) {
        if(format[i] == '%') {
            i++;

            if(format[i] == 0) {
                io_putChar('%');
                continue;
            }

            switch (format[i]) {
                case 'd': case 'i': {
                    char buf[12];
                    str_fromInt(va_next(args, int), buf);
                    io_print(buf);
                    break;
                }

                case 'x': {
                    char buf[12];
                    str_fromHex(va_next(args, int), buf);
                    io_print(buf);
                    break;
                }

                case 's': {
                    io_print(va_next(args, const char*));
                    break;
                }

                case 'c': {
                    io_putChar(va_next(args, int));
                    break;
                }

                case 't': {
                    vga_setColor(va_next(args, int));
                    break;
                }

                case '%': {
                    io_putChar('%');
                    break;
                }
                
                default: {
                    io_putChar('%');
                    io_putChar(format[i]);

                    break;
                }
            }
        } else {
            io_putChar(format[i]);
        }
    }
}

char io_getChar() {
    kb_key k;

    while((k = kb_getKey()).ch == 0 || k.ev != press);

    return k.ch;
}

void io_getStr(char* buf) {
    kb_key key;
    str_sz i = 0;

    while(!((key = kb_getKey()).sc == KB_KEY_ENTER && key.ev == press)) {
        if(key.ev == release)
            continue;

        switch (key.sc) {
            case KB_KEY_BACKSPACE: case KB_KEY_LEFT: {
                if(i > 0) {
                    io_putChar('\b');
                    i--;
                }

                break;
            }

            case KB_KEY_TAB:
                break;

            default: {
                if(key.ch != 0) {
                    buf[i] = key.ch;
                    io_putChar(key.ch);
                    i++;
                }

                break;
            }
        }
    }

    io_putChar('\n');

    buf[i] = 0;
}