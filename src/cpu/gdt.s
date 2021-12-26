.globl GDT_desc

GDT_start:
    nullDesc:
        .word 0x0000
        .word 0x0000
        .byte 0x0000
        .byte 0b00000000
        .byte 0b00000000
        .byte 0x0000
    codeDesc:
        .word 0xFFFF
        .word 0x0000
        .byte 0x0000
        .byte 0b10011010
        .byte 0b11001111
        .byte 0x0000
    dataDesc:
        .word 0xFFFF
        .word 0x0000
        .byte 0x0000
        .byte 0b10010010
        .byte 0b11001111
        .byte 0x0000
GDT_end:

GDT_desc:
    .word GDT_end - GDT_start - 1
    .long GDT_start