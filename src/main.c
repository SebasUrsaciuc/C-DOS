#include "def.h"
#include "ps2.h"
#include "io.h"
#include "string.h"
#include "kb.h"
#include "int.h"
#include "pit.h"
#include "dymem.h"
#include "vga.h"
#include "disk.h"

void start() {
    vga_clear();

    mem_init(0x100000, 0x100000);
    int_init();
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