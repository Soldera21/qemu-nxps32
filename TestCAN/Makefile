# Variables
# Engine
ARM_GNU = arm-none-eabi

# Target executable 
TARGET = can.elf
# Source files
SRCS = main.c uart.c can.c
SRCS += Startup_Code/exceptions.c Startup_Code/nvic.c Startup_Code/startup.c Startup_Code/system.c
# Assembly files
ASFL = Startup_Code/startup_cm7.s Startup_Code/Vector_Table.s
# Linker files
LNFL = Startup_Code/linker_flash_s32k358.ld
# Object files
OBJS = $(SRCS:.c=.o)
# Assembly object
ASOB = $(ASFL:.s=.o)

# Rules 
# Default target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS) $(ASOB)
	arm-none-eabi-gcc -T $(LNFL) -o $(TARGET) "@Startup_Code/TestUART.args" $(OBJS) $(ASOB) -lc -lm -lgcc

# Rule to compile source files into object files
Startup_Code/%.o: Startup_Code/%.c
	$(ARM_GNU)-gcc "@Startup_Code/exceptions.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"

./%.o: ./%.c
	$(ARM_GNU)-gcc "@Startup_Code/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"

%.o: %.s
	$(ARM_GNU)-gcc "@Startup_Code/Vector_Table.args" -o "$@" "$<"

# Clean rule to remove compiled files
clean:
	rm -f *.d *.o *.elf
	rm -f Startup_Code/*.d Startup_Code/*.o Startup_Code/*.map

# GDB
gdb:
	gdb-multiarch $(TARGET)
# > target remote localhost:1234

debug:
	qemu-system-nxps32 -machine nxps32 -cpu cortex-m7 -kernel $(TARGET) -monitor none -nographic -serial stdio -s -S

run:
	qemu-system-nxps32 -machine nxps32 -cpu cortex-m7 -kernel $(TARGET) -monitor none -nographic -serial stdio

