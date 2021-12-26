.code16
.section .boot

// DEFINES
.equ PROGRAM_SPACE, 0x7E00
.equ KERNEL_SECTORS, 36

// LOAD THE KERNEL ONTO RAM
mov $0x02, %Ah
mov $KERNEL_SECTORS, %Al
mov $PROGRAM_SPACE, %BX
mov $0x00, %Ch
mov $0x02, %Cl
mov $0x00, %Dh
int $0x13

// JUMP OFF THE BOOTLOADER
jmp start

// INFINITE LOOP IN CASE OF FAILURE
jmp .