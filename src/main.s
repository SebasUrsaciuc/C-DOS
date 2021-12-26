.globl start

.code16
start:
    cli
    call enableProt
    call gdt_load
    jmp protMode

enableProt:
    mov %CR0, %EAX
    or $1, %EAX
    mov %EAX, %CR0
    ret

.code32
protMode:
    call kmain
    call sys_kill
    jmp .
