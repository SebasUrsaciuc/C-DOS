jmp gdt_asm_end

GDT_start:
    nullDesc:
        dw 0x0000
        dw 0x0000
        db 0x0000
        db 00000000b
        db 00000000b
        db 0x0000
    codeDesc:
        dw 0xFFFF
        dw 0x0000
        db 0x0000
        db 10011010b
        db 11001111b
        db 0x0000
    dataDesc:
        dw 0xFFFF
        dw 0x0000
        db 0x0000
        db 10010010b
        db 11001111b
        db 0x0000
GDT_end:

GDT_desc:
    dw GDT_end - GDT_start - 1
    dd GDT_start

CODE_SEG equ codeDesc - GDT_start
DATA_SEG equ dataDesc - GDT_start

gdt_asm_end: