#include "cpu/int.h"
#include "cpu/idt.h"
#include "drv/ps2.h"
#include "drv/kb.h"
#include "drv/pit.h"
#include "drv/vga.h"
#include "drv/disk.h"
#include "misc/io.h"
#include "misc/string.h"
#include "sys/dymem.h"

#include "def.h"

void start() {
    vga_clear();

    mem_init(0x100000, 0x100000);
    int_init();
    idt_init();
    pit_init();
    kb_init();

    io_println("Kernel loaded successfully!\n");

    char in[128];

    while(true) {
        io_print("> ");

        io_getStr(in);

        if(str_eqi(in, "reset")) {
            ps2_reset();
        } else if(str_eqi(in, "cls")) {
            vga_clear();
        } else if(str_len(in) > 0) {
            io_println("Bad command!\n");
        }
    }
}