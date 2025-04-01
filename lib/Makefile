OBJDIR := obj

HFILES := $(wildcard *.h) $(wildcard float/*.h)
CFILES := $(wildcard *.c) $(wildcard float/*.c)
ASFILES := $(wildcard *.S)
TARGET := lib.a
OBJ := $(ASFILES:%.S=$(OBJDIR)/%.o) $(CFILES:%.c=$(OBJDIR)/%.o)

LIBINC = ./include/
KERNINC = ./../KERNEL/include/

dummy := $(shell mkdir -p $(OBJDIR)) $(shell mkdir -p $(OBJDIR)/float)

$(TARGET): $(OBJ)
	$(AR) rcs $@ $^

$(OBJDIR)/%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

$(OBJDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LIBINC) -I$(KERNINC)

.PHONY: clean
clean:
	rm -rf obj/
	rm -f $(TARGET)
