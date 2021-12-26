.section .boot
.code16

boot:
    call loadProg

    jmp start
    jmp .

loadProg:
    mov $0x02, %Ah
    mov $progSects, %Al
    mov $progStart, %BX
    mov $0x00, %Ch
    mov $0x02, %Cl
    mov $0x00, %Dh
    int $0x13
    ret