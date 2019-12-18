// The addresses of the Broadcom interrupt controller registers.
//
// These are defined on page 112 of the Broadcom BCM2837 ARM Peripherals
// Manual. Note that we specify the ARM physical addresses of the
// peripherals, which have the address range 0x3F000000 to 0x3FFFFFFF.
// These addresses are mapped by the VideoCore Memory Management Unit (MMU)
// onto the bus addresses in the range 0x7E000000 to 0x7EFFFFFF.
#define MMIO_BASE       		0x3F000000

#define IRQ_BASIC_PENDING       ((volatile unsigned int *)(MMIO_BASE + 0x0000B200))
#define IRQ_PENDING_1           ((volatile unsigned int *)(MMIO_BASE + 0x0000B204))
#define IRQ_PENDING_2           ((volatile unsigned int *)(MMIO_BASE + 0x0000B208))
#define IRQ_FIQ_CONTROL         ((volatile unsigned int *)(MMIO_BASE + 0x0000B20C))
#define IRQ_ENABLE_IRQS_1       ((volatile unsigned int *)(MMIO_BASE + 0x0000B210))
#define IRQ_ENABLE_IRQS_2       ((volatile unsigned int *)(MMIO_BASE + 0x0000B214))
#define IRQ_ENABLE_BASIC_IRQS   ((volatile unsigned int *)(MMIO_BASE + 0x0000B218))
#define IRQ_DISABLE_IRQS_1      ((volatile unsigned int *)(MMIO_BASE + 0x0000B21C))
#define IRQ_DISABLE_IRQS_2      ((volatile unsigned int *)(MMIO_BASE + 0x0000B220))
#define IRQ_DISABLE_BASIC_IRQS	((volatile unsigned int *)(MMIO_BASE + 0x0000B224))
