#include "def.h"
#include "ps2.h"
#include "io.h"
#include "string.h"
#include "kb.h"
#include "int.h"
#include "pit.h"
#include "dymem.h"

void start() {
    clrs();

    initheap(0x100000, 0x100000);
    initidt();
    initpit();
    initkb();

    puts("Kernel loaded successfully!\n");

    char* in[128];

    while(true) {
        sputs("> ");

        gets(in);

        if(streqi(in, "reset")) {
            reset();
        } else if(streqi(in, "cls")) {
            clrs();
        } else if(strlen(in) > 0) {
            puts("Bad command!\n");
        }
    }
}