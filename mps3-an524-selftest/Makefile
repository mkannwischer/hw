# Makefile for MPS3-AN524

CFLAGS += \
	-O2 \
	-Wall -Wextra -Wshadow \
	-MMD \
	-fno-common \
	-ffunction-sections \
	-fdata-sections \
	$(CPPFLAGS)

LDFLAGS += \
	-Wl,--gc-sections \
	-L.

LDLIBS += -lhal
LIBDEPS = libhal.a

OBJS = test.c.o

all: test.elf

objs = $(addsuffix .o,$(1))
PLATFORM ?= mps3-an524
include platform/$(PLATFORM).mk

run: test.elf
	qemu-system-arm -M mps3-an524 -nographic -semihosting -kernel $<

%.elf: %.c.o $(OBJS) $(LDSCRIPT) $(LIBDEPS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -Wl,--start-group $(LDLIBS) -Wl,--end-group

%.a:
	@echo "  AR      $@"
	$(AR) rcs $@ $(filter %.o,$^)

%.c.o: %.c
	@echo "  CC      $@"
	$(CC) -c -o $@ $(CFLAGS) $<

%.S.o: %.S
	@echo "  AS      $@"
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o *.d platform/*.o platform/*.d *.elf *.bin *.a

-include $(OBJS:.o=.d)
