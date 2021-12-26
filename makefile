## PATHS ##
ASM_PATH = asm
SRC_PATH = src
INC_PATH = include
OUT_PATH = out
TMP_PATH = $(OUT_PATH)/tmp

LD_SCRIPT = link.ld
OUT = $(OUT_PATH)/os.bin

## FILES ##
SRCS = $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/**/*.c)
ASMS = $(wildcard $(SRC_PATH)/*.s $(SRC_PATH)/**/*.s)

C_OBJS = $(patsubst $(SRC_PATH)/%.c, $(TMP_PATH)/%.co, $(SRCS))
S_OBJS = $(patsubst $(SRC_PATH)/%.s, $(TMP_PATH)/%.so, $(ASMS))

C_OBJS_CNT = $(words $(C_OBJS))
S_OBJS_CNT = $(words $(S_OBJS))

## COMPILER ##
# To use Intel ASM: (-masm=intel)
CC = gcc
CC_ARGS = -fno-pic -ffreestanding -mno-red-zone -m32 -I$(INC_PATH) -c -mgeneral-regs-only -O2

## LINKER ##
LD = ld
LD_ARGS = -melf_i386 -T$(LD_SCRIPT)

## ASSEMBLER ##
ASM = as
ASM_ARGS = -I$(SRC_PATH) --32 -O2 -nostartfiles -nostdlib

all: compile clear

compile: $(S_OBJS) $(C_OBJS)
	echo Linking $(C_OBJS_CNT) C object files and $(S_OBJS_CNT) ASM object files
	$(LD) $(LD_ARGS) $(S_OBJS) $(C_OBJS) -o $(OUT)

$(TMP_PATH)/%.so: $(SRC_PATH)/%.s
	echo Compiling ASM source: $<
	mkdir -p $(@D)
	$(ASM) $(ASM_ARGS) $< -o $@

$(TMP_PATH)/%.co: $(SRC_PATH)/%.c
	echo Compiling C source: $<
	mkdir -p $(@D)
	$(CC) $(CC_ARGS) $< -o $@

clear:
	echo Cleaning up...
	rm -r $(TMP_PATH)/*