OUTPUT_FORMAT(binary)

SECTIONS {
    . = 0x7C00;

    .boot : {
        *(.boot);

        . = 0x1FE;

        SHORT(0xAA55);
    }

    progStart = 0x7E00;
    . = progStart;

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

    progEnd = .;
    progSize = progEnd - progStart;
    progSects = (progSize / 512) + 1 - ((512 - (progSize % 512)) / 512);
}