CFLAGS += \
	-O3 \
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
LIBDEBS=libhal.a

OBJS= test.c.o

all: test.elf

objs = $(addsuffix .o,$(1))
PLATFORM ?= mps3-an555
include platform/$(PLATFORM).mk


run-test.elf: test.elf
	qemu-system-arm -M mps3-an555 -nographic -semihosting -kernel $<


%.elf: %.c.o $(OBJS) $(LDSCRIPT) $(LIBDEBS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -Wl,--start-group $(LDLIBS) -Wl,--end-group

%.a:
	@echo "  AR      $@"
	$(Q)[ -d $(@D) ] || mkdir -p $(@D)
	$(Q)$(AR) rcs $@ $(filter %.o,$^)

%.c.o: %.c
	@echo "  CC      $@"
	$(Q)[ -d $(@D) ] || mkdir -p $(@D)
	$(Q)$(CC) -c -o $@ $(CFLAGS) $<

%.c.S: %.c
	@echo "  CC      $@"
	$(Q)[ -d $(@D) ] || mkdir -p $(@D)
	$(Q)$(CC) -S -o $@ $(CFLAGS) $<

%.S.o: %.S
	@echo "  AS      $@"
	$(Q)[ -d $(@D) ] || mkdir -p $(@D)
	$(Q)$(CC) -c -o $@ $(CFLAGS) $<

%.s.o: %.s
	@echo "  AS      $@"
	$(Q)[ -d $(@D) ] || mkdir -p $(@D)
	$(Q)$(CC) -c -o $@ $(CFLAGS) $<


.PHONY: clean
clean:
	rm -rf *.o *.d platform/*.o platform/*.d test.elf *.a

-include $(OBJS:.o=.d)
