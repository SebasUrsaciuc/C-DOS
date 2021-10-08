[org 0x7C00]

; READ DISK ;
mov [BOOT_DISK], Dl
call readDisk

; SWITCH TO PROTECTED MODE ;
cli
lgdt [GDT_desc]
mov EAX, CR0
or EAX, 1
mov CR0, EAX

; FAR JUMP ;
call CODE_SEG:PROGRAM_SPACE
jmp $

; INCLUDE ;
%include "asm/disk.asm"
%include "asm/gdt.asm"

; FILL BOOT SECT ;
times (512 - 2) - ($ - $$) db 0
dw 0xAA55