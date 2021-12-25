# PATHS #
ASM_PATH = asm
SRC_PATH = src
INC_PATH = include
OUT_PATH = out
TMP_PATH = $(OUT_PATH)/tmp

# FILES #
SRCS = $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/**/*.c)
ASMS = $(wildcard $(SRC_PATH)/*.s $(SRC_PATH)/**/*.s)

C_OBJS = $(patsubst $(SRC_PATH)/%.c, $(TMP_PATH)/%.co, $(SRCS))
S_OBJS = $(patsubst $(SRC_PATH)/%.s, $(TMP_PATH)/%.so, $(ASMS))

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
ASM_ARGS = -felf32 -I$(SRC_PATH)

all: assembly cxx link bin clean

assembly:
	$(ASM) -fbin $(SRC_PATH)/boot.asm -o $(TMP_PATH)/boot.bin

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

bin:
	cat $(TMP_PATH)/boot.bin $(TMP_PATH)/kernel.bin > $(OUT_PATH)/dos.bin

clean:
	rm -r $(TMP_PATH)/*