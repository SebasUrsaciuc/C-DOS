.code16
.section .boot

// LOAD THE KERNEL ONTO RAM
mov $0x02, %Ah
mov $progSects, %Al
mov $progSpace, %BX
mov $0x00, %Ch
mov $0x02, %Cl
mov $0x00, %Dh
int $0x13

// JUMP OFF THE BOOTLOADER
jmp start

// INFINITE LOOP IN CASE OF FAILURE
jmp .