.globl gdt_desc

gdt_start:
    gdt_nullDesc:
        .word 0x0000
        .word 0x0000
        .byte 0x0000
        .byte 0b00000000
        .byte 0b00000000
        .byte 0x0000
    gdt_codeDesc:
        .word 0xFFFF
        .word 0x0000
        .byte 0x0000
        .byte 0b10011010
        .byte 0b11001111
        .byte 0x0000
    gdt_dataDesc:
        .word 0xFFFF
        .word 0x0000
        .byte 0x0000
        .byte 0b10010010
        .byte 0b11001111
        .byte 0x0000
gdt_end:

gdt_desc:
    .word gdt_end - gdt_start - 1
    .long gdt_start