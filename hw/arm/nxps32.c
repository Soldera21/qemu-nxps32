/*
 * NXPS32 Machine Model
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/boards.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-clock.h"
#include "qemu/error-report.h"
#include "hw/arm/s32k358_soc.h"
#include "hw/arm/boot.h"

/* Main SYSCLK frequency in Hz (320MHz) */
#define SYSCLK_FRQ 320000000ULL

static void nxps32_init(MachineState *machine)
{
    DeviceState *dev;
    Clock *sysclk;

    /* This clock doesn't need migration because it is fixed-frequency */
    sysclk = clock_new(OBJECT(machine), "SYSCLK");
    clock_set_hz(sysclk, SYSCLK_FRQ);

    dev = qdev_new(TYPE_S32K358_SOC);

    /** */
    //object_property_add_child(OBJECT(machine), "soc", OBJECT(dev));
    /** */

    qdev_connect_clock_in(dev, "sysclk", sysclk);
    sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_fatal);

    armv7m_load_kernel(ARM_CPU(first_cpu), machine->kernel_filename,
                       0, FLASH_SIZE);
}

static void nxps32_machine_init(MachineClass *mc)
{
    static const char * const valid_cpu_types[] = {
        ARM_CPU_TYPE_NAME("cortex-m7"),
        NULL
    };

    mc->desc = "NXPS32 Machine (Cortex-M7)";
    mc->init = nxps32_init;
    mc->valid_cpu_types = valid_cpu_types;
    mc->ignore_memory_transaction_failures = true;
}

DEFINE_MACHINE("nxps32", nxps32_machine_init)
