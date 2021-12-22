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

; SET DATA SEGEMENT
mov AX, DATA_SEG
mov DS, AX
mov SS, AX
mov ES, AX
mov FS, AX
mov GS, AX

; SET EXTENDED STACK
mov EBP, 0x90000
mov ESP, EBP

; FAR JUMP ;
jmp CODE_SEG:PROGRAM_SPACE