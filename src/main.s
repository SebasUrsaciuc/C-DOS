[bits 16]

; DEFINES ;
%include "cpu/gdt.s"
extern start
extern sys_kill

; SWITCH TO PROTECTED MODE ;
cli
lgdt [GDT_desc]
mov EAX, CR0
or EAX, 1
mov CR0, EAX

; FAR JUMP ;
jmp CODE_SEG:protMode

; PROTECED MODE ;
[bits 32]
protMode:

; SET DATA SEGEMENT ;
mov AX, DATA_SEG
mov DS, AX
mov SS, AX
mov ES, AX
mov FS, AX
mov GS, AX

; JUMP TO C CODE ;
call start

; KILL IN CASE OF FAILURE ;
call sys_kill
jmp $