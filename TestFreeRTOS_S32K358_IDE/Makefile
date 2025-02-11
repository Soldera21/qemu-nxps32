# Target executable 
TARGET = Debug_FLASH/TestFreeRTOS_S32K358_IDE.elf

# GDB
gdb:
	gdb-multiarch $(TARGET)
# > target remote localhost:1234

debug:
	qemu-system-nxps32 -machine nxps32 -cpu cortex-m7 -kernel $(TARGET) -monitor none -nographic -serial stdio -s -S

run:
	qemu-system-nxps32 -machine nxps32 -cpu cortex-m7 -kernel $(TARGET) -monitor none -nographic -serial stdio

