[org 0x7C00]

jmp boot

;;=================;;
;; PARAMETER BLOCK ;;
;;=================;;
%include "asm/param.asm"

;;================;;
;; BOOT PROCEDURE ;;
;;================;;
boot:
%include "asm/main.asm"

;;=====================;;
;; UNUSED SPACE FILLER ;;
;;=====================;;
times (512 - 2) - ($ - $$) db 0
dw 0xAA55