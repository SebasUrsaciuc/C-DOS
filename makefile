# PATHS #
ASM_PATH = asm
SRC_PATH = src
INC_PATH = include
OUT_PATH = out
TMP_PATH = $(OUT_PATH)/tmp

# FILES #
SRCS = $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/**/*.c)
OBJS = $(patsubst $(SRC_PATH)/%.c, $(TMP_PATH)/%.o, $(SRCS))

# COMPILER #
CC_OPT_LVL = 2

CC = gcc
CC_ARGS = -masm=intel -fno-pic -ffreestanding -mno-red-zone -m32 -I$(INC_PATH) -c -mgeneral-regs-only -O$(CC_OPT_LVL)

# LINKER #
LD_SCRIPT = link.ld
LD_TARGET = elf_i386

LD = ld
LD_ARGS = -m$(LD_TARGET)

# ASSEMBLER #
ASM = nasm

all: assembly cxx link bin clean

assembly:
	$(ASM) -fbin $(ASM_PATH)/boot.asm -o $(TMP_PATH)/boot.bin
	$(ASM) -felf32 $(ASM_PATH)/ext.asm -o $(TMP_PATH)/ext.o

cxx: $(OBJS)
	$(LD) $(LD_ARGS) -r $(OBJS) -o $(TMP_PATH)/kernel.o

$(TMP_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(@D)
	$(CC) $(CC_ARGS) $< -o $@

link:
	$(LD) $(LD_ARGS) -T$(LD_SCRIPT)

bin:
	cat $(TMP_PATH)/boot.bin $(TMP_PATH)/kernel.bin > $(OUT_PATH)/dos.bin

clean:
	rm -r $(TMP_PATH)/*