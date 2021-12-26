.globl gdt_dsc
.globl gdt_load

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

gdt_dsc:
    .word gdt_end - gdt_start - 1
    .long gdt_start

.code16
gdt_load:
    lgdt (gdt_dsc)

    mov $0x10, %AX
    mov %AX, %DS
    mov %AX, %ES
    mov %AX, %FS
    mov %AX, %GS
    mov %AX, %SS

    jmp $0x08, $1f

    1:
    .code32
    retw
