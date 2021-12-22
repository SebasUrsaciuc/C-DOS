#include "sys.h"

#include "int.h"
#include "vga.h"
#include "io.h"
#include "string.h"
#include "kb.h"
#include "pit.h"
#include "sound.h"

void sys_panic(const char* mot) {
    vga_setCrs(VGA_CRS_OFF);
    vga_setColor(VGA_CLR_BG_BLUE | VGA_CLR_FG_SILVER);
    vga_clear();

    io_println("Something went wrong during the kernel execution!");

    io_putChar('\n');
    io_println("The motivation of the panic is:");
    io_println(mot);
    io_putChar('\n');

    io_println("Try rebooting your system!");

    snd_play(800);

    sys_kill();
}

void sys_kill() {
    int_set(false);
    
    sys_hlt();
}

void sys_wait(uint16 ms) {
    uint32 end = pit_getTime() + ms;

    while(pit_getTime() < end) {
        sys_hlt();
    }
}