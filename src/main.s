.globl start

.code16
start:
    // SWITCH TO PROTECTED MODE
    cli
    lgdt (gdt_desc)
    mov %CR0, %EAX
    or $1, %EAX
    mov %EAX, %CR0

    // FAR JUMP
    jmp $0x08, $protMode


.code32
protMode:
    // SET DATA SEGEMENT
    mov $0x10, %AX
    mov %AX, %DS
    mov %AX, %ES
    mov %AX, %FS
    mov %AX, %GS
    mov %AX, %SS

    // JUMP TO C CODE
    call kmain

    // KILL IN CASE OF FAILURE
    call sys_kill
    jmp .