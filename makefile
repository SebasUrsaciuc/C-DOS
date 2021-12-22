# GENERAL #
DEBUG = false
BITS = 32

# PATHS #
ASM_PATH = asm
SRC_PATH = src
INC_PATH = include
OUT_PATH = out
TMP_PATH = $(OUT_PATH)/tmp

# FILES #
ifeq ($(DEBUG), false)
OBJS_EXT = o
else
OBJS_EXT = s
endif

SRCS = $(wildcard $(SRC_PATH)/*.c)
OBJS = $(patsubst $(SRC_PATH)/%.c, $(TMP_PATH)/%.$(OBJS_EXT), $(SRCS))

# COMPILER #
CC_OPT_LVL = 2

CC = gcc
CC_ARGS = -fno-pic -ffreestanding -mno-red-zone -m$(BITS) -I$(INC_PATH) -c -mgeneral-regs-only -O$(CC_OPT_LVL)

ifneq ($(DEBUG), false)
CC_ARGS += -S
endif

# LINKER #
LD_SCRIPT = link.ld
LD_TARGET = elf_i386

LD = ld
LD_ARGS = -m$(LD_TARGET)

# ASSEMBLER #
ASM = nasm

ifeq ($(DEBUG), false)
all: assembly cxx link bin clean
else
all: $(OBJS)
endif

assembly:
	$(ASM) -fbin $(ASM_PATH)/boot.asm -o $(TMP_PATH)/boot.bin
	$(ASM) -felf$(BITS) $(ASM_PATH)/ext.asm -o $(TMP_PATH)/ext.o

cxx: $(OBJS)
	$(LD) $(LD_ARGS) -r $(OBJS) -o $(TMP_PATH)/kernel.o

$(TMP_PATH)/%.$(OBJS_EXT): $(SRC_PATH)/%.c
	$(CC) $(CC_ARGS) $< -o $@

link:
	$(LD) $(LD_ARGS) -T$(LD_SCRIPT)

bin:
	cat $(TMP_PATH)/boot.bin $(TMP_PATH)/kernel.bin > $(OUT_PATH)/dos.bin

clean:
	rm $(TMP_PATH)/*