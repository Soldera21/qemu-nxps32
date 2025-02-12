S32K3X8EVB-Q289 Emulation in Qemu
================
### Group 18
**Components:** *Bertolami Carmelo (s345963), Frigo Matteo (s338605), Simoncini Marco (s341631), Soldera Marco(s338823)*

## Project Structure
The version of Qemu used in this project is qemu-stable-8.2 from GitHub (https://github.com/qemu/qemu/tree/stable-8.2). Below is shown the structure of the folders containing files added or modified by us to emulate the S32K3X8EVB-Q289 board in the project. \
The four main folders are:
* ```hw```: implementation of baords and their components;
* ```include```: headers of Qemu boards and other components;
* ```net```: implementation of network components;
* ```target```: implementation of the CPUs used on the boards but not changed by us.

The official documentation of Qemu is in ```docs``` folder; in ```docs-project-group18``` the LaTeX and PPT documentation of the project of our group can be found.

```
.
├── configs/
│   └── devices/
│       └── arm-softmmu/
│           └── default.mak --> list of ARM platforms included in build
├── docs-project-group18/
│   └── ... --> LaTeX and PPT documentation of the project
├── hw/
│   ├── arm/
│   │   ├── nxps32.c --> main board file
│   │   └── s32k358_soc.c --> SoC init with all its components
│   ├── char/
│   │   └── s32k358_uart.c --> logic of UART
│   ├── misc/
│   │   └── s32k358_syscfg.c --> logic of SYSCFG
│   └── net/
│       └── can/
│           └── s32k358_can.c --> logic of CAN
├── include/
│   ├── hw/
│   │   ├── arm/
│   │   │   └── s32k358_soc.h --> header and data structure of SoC
│   │   ├── char/
│   │   │   ├── s32k358_uart.h --> header and data structure of UART
│   │   │   └── s32k358_uart_mapping.h --> mapping of UART registers
│   │   ├── misc/
│   │   │   └── s32k358_syscfg.h --> header and data structure of SYSCFG
│   │   └── net/
│   │       ├── s32k358_can.h --> header and data structure of CAN
│   │       └── s32k358_can_mapping.h --> mapping of CAN registers
│   └── net/
│       └── can_emu.h --> header file of CAN bus
├── net/
│   └── can/
│       └── can_core.c --> logic of CAN bus
├── targets/
│   └── ... --> implementation of CPUs
│
├── TestCAN
├── TestCAN_MultiTask_S32K358_IDE
├── TestFreeRTOS_S32K358_IDE
├── TestUART
└── TestUART_S32K358_IDE
```

The demos that are included in this project are:
* **TestCAN**: compilation of demo code for CAN single task with ad-hoc Makefile and with all the needed libraries included;
* **TestCAN_MultiTask_S32K358_IDE**: compilation of demo code for CAN in multi task environment like FreeRTOS through the NXP IDE.
* **TestFreeRTOS_S32K358_IDE**: compilation of demo code of FreeRTOS with two tasks and a semaphore through the NXP IDE.
* **TestUART**: compilation of demo code for UART with ad-hoc Makefile and with all the needed libraries included;
* **TestUART_S32K358_IDE**: compilation of demo code for UART through the NXP IDE.

To achieve correct compilation of the code also ```meson.build``` and ```Kconfig``` have been properly modified in the folders where new files have been added.


## Build
The compilation of the project is made through the use of Meson and Kconfig mechanisms. After cloning the repository and entering the root folder of the project the following commands needs to be executed:

```
./configure
make -j 16
```

The ```make``` command is used also at every modification of the code of Qemu to recompile only the needed parts.


## Usage
After the build step, the execution of the code is done through the executable file in ```build``` folder named ```qemu-system-arm```. A good practise could be to create a symlink in a folder included in PATH to use modified Qemu from every folder and with a different name with respect to the original version of Qemu:

```
ln -s /usr/local/bin/qemu-system-nxp32 <path-to-new-qemu-system-arm>
```

Now the code can be executed with ```qemu-system-nxps32 <executable>``` like a normal Qemu build but for the new board.

Main flags used:
* -machine nxps32 --> specify the board
* -cpu cortex-m7 --> specify the cpu
* -kernel \<path-to-binary\> --> specify to load kernel binary for emulation
* -monitor none --> disable Qemu monitor
* -nographic --> use only terminal output
* -serial stdio --> redirect serial to stdio
* -s -S --> enable GDB server and block execution at start
* -d cpu,exec,mmu,int --> enable logging of CPU, execution, MMU and interrupts


---
Part of this code and Demo Projects are licensed under a Creative Commons Attribution-NonCommercial 4.0 International License (view license files). \
https://creativecommons.org/licenses/by-nc/4.0/

