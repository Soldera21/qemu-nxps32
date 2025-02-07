# Variables
# Engine
ARM_GNU = arm-none-eabi
# Compiler flags
CFLAGS = -c -mcpu=cortex-m7 -mthumb
# Assembler flags
ASFLAGS = -mcpu=cortex-m7

# Target executable 
TARGET = uart.elf
# Source files
SRCS = main.c uart.c
# Assembly files
ASFL = startup.s
# Linker files
LNFL = linker.ld
# Object files
OBJS = $(SRCS:.c=.o)
# Assembly object
ASOB = $(ASFL:.s=.o)

# Rules 
# Default target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS) $(ASOB)
	$(ARM_GNU)-ld -T $(LNFL) $(ASOB) $(OBJS) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.c
	$(ARM_GNU)-gcc $(CFLAGS) $< -o $@

%.o: %.s
	$(ARM_GNU)-as $(ASFLAGS) $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f *.o *.elf

# GDB
gdb:
	gdb-multiarch $(TARGET)
# > target remote localhost:1234

debug:
	qemu-system-nxps32 -machine nxps32 -nographic -kernel $(TARGET) -s -S

run:
	qemu-system-nxps32 -machine nxps32 -nographic -kernel $(TARGET)

