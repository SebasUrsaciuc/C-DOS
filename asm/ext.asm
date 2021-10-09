%include "asm/gdt.asm"

extern start
extern die

[bits 32]
mov AX, DATA_SEG
mov DS, AX
mov SS, AX
mov ES, AX
mov FS, AX
mov GS, AX

mov EBP, 0x90000
mov ESP, EBP

call start
call die