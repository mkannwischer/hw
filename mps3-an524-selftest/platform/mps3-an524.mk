ifndef _HAL
_HAL :=

CROSS_PREFIX ?= arm-none-eabi
RETAINED_VARS += CROSS_PREFIX

CC := $(CROSS_PREFIX)-gcc
AR := $(CROSS_PREFIX)-gcc-ar
LD := $(CC)
OBJCOPY := $(CROSS_PREFIX)-objcopy
SIZE := $(CROSS_PREFIX)-size

SYSROOT := $(shell $(CC) --print-sysroot)

CPPFLAGS += \
	--sysroot=$(SYSROOT) \
	-DFPGA_IMAGE

ARCH_FLAGS += \
	-mcpu=cortex-m33 \
	-mthumb \
	-mfloat-abi=soft

CPPFLAGS += \
	-Iplatform/

CFLAGS += \
	$(ARCH_FLAGS) \
	--specs=nosys.specs

LDSCRIPT = platform/mps3.ld

LDFLAGS += \
	--specs=nosys.specs \
	-Wl,--wrap=_write \
	-ffreestanding \
	-nostartfiles \
	-T$(LDSCRIPT) \
	$(ARCH_FLAGS)

HAL_SRC += \
	platform/startup_CMSDK_IoT.S \
	platform/system_CMSDK_IoT.c \
	platform/semihosting.c \
	platform/uart_stdout.c
HAL_OBJ = $(call objs,$(HAL_SRC))

OBJ += $(HAL_OBJ)

libhal.a: $(HAL_OBJ)

LDLIBS += -lhal
LIBDEPS += libhal.a

endif
