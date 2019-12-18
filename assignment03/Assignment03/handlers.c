// This file contains C functions to handle particular kinds of exceptions.
// Only a function to handle IRQ exceptions is currently implemented.

// Header files
#include "uart.h"
#include "gpio.h"
#include "irq.h"
#include "sysreg.h"

// Reference to the global shared value
extern unsigned int sharedValue;

////////////////////////////////////////////////////////////////////////////////
//
//  Function:       IRQ_handler
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function first prints out some basic information about
//                  the state of the interrupt controller, GPIO pending
//                  interrupts, and selected system registers. It then
//                  determines the particular kind of pending interrupt (which
//                  for the moment is a rising edge event on GPIO pin 23). The
//                  interrupt is cleared, and interrupt is handled in a simple-
//                  minded way by incrementing the shared global variable.
//
////////////////////////////////////////////////////////////////////////////////

void IRQ_handler()
{
    //unsigned int r;

    // Print out exception type
    uart_puts("\nInside IRQ exception handler:\n");

    // Handle GPIO interrupts in general
    if (*IRQ_PENDING_2 == (0x1 << 20)) {

      // Handle the interrupt associated with GPIO pin 23
      if (*GPEDS0 == (0x1 << 23)) {
        // Clear the interrupt by writing a 1 to the GPIO Event Detect
        // Status Register at bit 23 (p. 96 of the Broadcom Manual)
        *GPEDS0 = (0x1 << 23);
        //if we change the sharedValue
        sharedValue = 0;
      }
      // Handle the interrupt associated with GPIO pin 23
      else if (*GPEDS0 == (0x1 << 22)) {
        // Clear the interrupt by writing a 1 to the GPIO Event Detect
        // Status Register at bit 22 (p. 96 of the Broadcom Manual)
        *GPEDS0 = (0x1 << 22);
        sharedValue = 1;
      }
    }
    // Return to the IRQ exception handler stub
    return;
}
