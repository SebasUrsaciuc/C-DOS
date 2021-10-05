#include "sys.h"

#include "int.h"
#include "color.h"
#include "io.h"
#include "string.h"
#include "kb.h"
#include "pit.h"

void hlt() {
    asm("hlt");
}

void panic(const char* mot) {
    setcurs(CUR_SH_DISABLED);
    setclr(VGA_CLR_BG_BLUE | VGA_CLR_FG_SILVER);
    clrs();

    puts("Something went wrong during the kernel execution!");

    puts("");
    puts("The motivation of the panic is:");
    puts(mot);
    puts("");

    puts("Try rebooting your system!");

    setintf(false);
    hlt();
}

void wait(uint16 ms) {
    uint32 end = gettime() + ms;

    while(gettime() < end) {
        hlt();
    }
}