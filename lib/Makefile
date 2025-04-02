OBJDIR := obj

HFILES := $(wildcard *.h)
CFILES := $(wildcard *.c)
ASFILES := $(wildcard *.S)
TARGET := lib.a
OBJ := $(ASFILES:%.S=$(OBJDIR)/%.o) $(CFILES:%.c=$(OBJDIR)/%.o)

dummy := $(shell mkdir -p $(OBJDIR))

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
