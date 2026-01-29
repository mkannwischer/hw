# Makefile for MPS3-AN524 using AN524 selftest code
# Uses GCC toolchain

CROSS_PREFIX ?= arm-none-eabi
CC = $(CROSS_PREFIX)-gcc
AS = $(CROSS_PREFIX)-gcc
LD = $(CROSS_PREFIX)-gcc
OBJCOPY = $(CROSS_PREFIX)-objcopy
SIZE = $(CROSS_PREFIX)-size

# Architecture flags - Cortex-M33, soft float (no FPU needed)
ARCH_FLAGS = -mcpu=cortex-m33 -mthumb -mfloat-abi=soft

# Compiler flags
CFLAGS = $(ARCH_FLAGS)
CFLAGS += -DFPGA_IMAGE
CFLAGS += -Iplatform
CFLAGS += -O2
CFLAGS += -Wall
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += --specs=nosys.specs

# Assembler flags
ASFLAGS = $(ARCH_FLAGS)
ASFLAGS += --specs=nosys.specs

# Linker flags
LDFLAGS = $(ARCH_FLAGS)
LDFLAGS += -Tplatform/mps3.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += --specs=nosys.specs
LDFLAGS += -nostartfiles

# Source files
SRCS = test.c
SRCS += platform/system_CMSDK_IoT.c
SRCS += platform/uart_stdout.c
SRCS += platform/retarget.c

ASM_SRCS = platform/startup_CMSDK_IoT.S

# Object files
OBJS = $(SRCS:.c=.o)
OBJS += $(ASM_SRCS:.S=.o)

# Target
TARGET = test

all: $(TARGET).elf $(TARGET).bin
	$(SIZE) $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin

run: $(TARGET).elf
	qemu-system-arm -M mps3-an524 -nographic -kernel $<

.PHONY: all clean run
