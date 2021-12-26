INPUT (
    out/tmp/kernel.o
)

OUTPUT_FORMAT(binary)

OUTPUT (
    out/dos.bin
)

SECTIONS {
    . = 0x7C00;

    .boot : {
        *(.boot);

        . = 0x1FE;

        SHORT(0xAA55);
    }

    . = 0x7E00;

    .text : ALIGN(0x1000) {
        *(.text);
    }
    
    .data : ALIGN(0x1000) {
        *(.data);
    }

    .rodata : ALIGN(0x1000) {
        *(.rodata);
    }

    .bss : ALIGN(0x1000) {
        *(COMMON);
        *(.bss);
    }
}