; DATA ;
PROGRAM_SPACE equ 0x8000
SECTORS equ 36
BOOT_DISK: db 0

; FUNCTIONS ;
readDisk:
    mov Ah, 0x02
    mov Al, SECTORS
    mov BX, PROGRAM_SPACE
    mov Ch, 0x00
    mov Cl, 0x02
    mov Dh, 0x00
    mov Dl, [BOOT_DISK]
    int 0x13
    ret