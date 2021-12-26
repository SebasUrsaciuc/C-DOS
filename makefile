## PATHS ##
ASM_PATH = asm
SRC_PATH = src
INC_PATH = include
OUT_PATH = out
TMP_PATH = $(OUT_PATH)/tmp

## FILES ##
SRCS = $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/**/*.c)
ASMS = $(wildcard $(SRC_PATH)/*.s $(SRC_PATH)/**/*.s)

C_OBJS = $(patsubst $(SRC_PATH)/%.c, $(TMP_PATH)/%.co, $(SRCS))
S_OBJS = $(patsubst $(SRC_PATH)/%.s, $(TMP_PATH)/%.so, $(ASMS))

## COMPILER ##
# To use Intel ASM: (-masm=intel)
CC = gcc
CC_ARGS = -fno-pic -ffreestanding -mno-red-zone -m32 -I$(INC_PATH) -c -mgeneral-regs-only -O2

## LINKER ##
LD_SCRIPT = link.ld
LD_TARGET = elf_i386

LD = ld
LD_ARGS = -m$(LD_TARGET)

## ASSEMBLER ##
ASM = as
ASM_ARGS = -I$(SRC_PATH) --32 -O2 -nostartfiles -nostdlib

all: cxx link clean

cxx: $(S_OBJS) $(C_OBJS)
	$(LD) $(LD_ARGS) -r $(S_OBJS) $(C_OBJS) -o $(TMP_PATH)/kernel.o

$(TMP_PATH)/%.so: $(SRC_PATH)/%.s
	mkdir -p $(@D)
	$(ASM) $(ASM_ARGS) $< -o $@

$(TMP_PATH)/%.co: $(SRC_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CC_ARGS) $< -o $@

link:
	$(LD) $(LD_ARGS) -T$(LD_SCRIPT)

clean:
	rm -r $(TMP_PATH)/*