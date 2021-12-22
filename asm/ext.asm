%include "asm/gdt.asm"

extern start
extern sys_kill

[bits 32]
call start
call sys_kill