%include "asm/disk.asm"
%include "asm/gdt.asm"

; LOAD KERNEL ;
call initDisk
call loadKernel

; SWITCH TO PROTECTED MODE ;
cli
lgdt [GDT_desc]
mov EAX, CR0
or EAX, 1
mov CR0, EAX

; FAR JUMP ;
jmp CODE_SEG:PROGRAM_SPACE