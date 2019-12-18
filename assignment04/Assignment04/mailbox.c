#include "gpio.h"

// Define mailbox registers. These can be found at:
// https://github.com/raspberrypi/firmware/wiki/Mailboxes
#define MAILBOX_BASE       (MMIO_BASE + 0x0000B880)

#define MAILBOX0_READ      ((volatile unsigned int *)(MAILBOX_BASE + 0x0))
#define MAILBOX0_PEEK      ((volatile unsigned int *)(MAILBOX_BASE + 0x10))
#define MAILBOX0_SENDER    ((volatile unsigned int *)(MAILBOX_BASE + 0x14))
#define MAILBOX0_STATUS    ((volatile unsigned int *)(MAILBOX_BASE + 0x18))
#define MAILBOX0_CONFIG    ((volatile unsigned int *)(MAILBOX_BASE + 0x1C))

#define MAILBOX1_WRITE     ((volatile unsigned int *)(MAILBOX_BASE + 0x20))
#define MAILBOX1_PEEK      ((volatile unsigned int *)(MAILBOX_BASE + 0x30))
#define MAILBOX1_SENDER    ((volatile unsigned int *)(MAILBOX_BASE + 0x34))
#define MAILBOX1_STATUS    ((volatile unsigned int *)(MAILBOX_BASE + 0x38))
#define MAILBOX1_CONFIG    ((volatile unsigned int *)(MAILBOX_BASE + 0x3C))

// Define mailbox bitmasks
#define MAILBOX_RESPONSE   0x80000000
#define MAILBOX_FULL       0x80000000
#define MAILBOX_EMPTY      0x40000000


// Allocate memory for the global mailbox buffer. It has to be
// quadword aligned, since the channel is encoded using the low-order
// 4 bits of its address.
volatile unsigned int  __attribute__((aligned(16))) mailbox_buffer[36];



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       mailbox_query
//
//  Arguments:      channel:     The mailbox channel number to use for
//                               the query
//
//  Returns:        TRUE (non-zero) if the query produces a valid response,
//                  FALSE (zero) otherwise.
//
//  Description:    This function sends a request to the video core using the
//                  mailbox mechansim. The request must be created in the
//                  global mailbox buffer, which also has room for any
//                  response. The request is encoded using the address of the
//                  mailbox buffer combined with the mailbox channel number.
//                  Once we confirm that mailbox 1 can accept a request, we
//                  make the request by writing this address to the mailbox 1
//                  write register. The video core then processes the request,
//                  and provides a response using mailbox 0. Once the response
//                  arrives, we make sure it is a response to our original
//                  request. If it is, we check to see if the video core was
//                  able to reply with a valid response. If so, we return
//                  a TRUE to calling code, which then can read the response
//                  in particular fields withing the global mailbox buffer.
//
////////////////////////////////////////////////////////////////////////////////

int mailbox_query(unsigned char channel)
{
    unsigned int address;

    // Combine the address of the mailbox buffer with the channel number
    address = (unsigned int)((unsigned long)&mailbox_buffer[0]) & 0xFFFFFFF0;
    address |= (channel & 0xF);

    // Keep polling mailbox 1 until it can accept a request
    while (*MAILBOX1_STATUS & MAILBOX_FULL)
	;

    // Write the address of our request to mailbox 1 with channel identifier
    *MAILBOX1_WRITE = address;

    // Wait for a response in mailbox 0
    while (1) {
	// Keep polling mailbox 0 until a response appears there
	while (*MAILBOX0_STATUS & MAILBOX_EMPTY)
	    ;

        // Make sure it is a response to our original request,
	// otherwise keep waiting for a response
        if (*MAILBOX0_READ == address) {
            // Return TRUE if is it a valid response, otherwise return FALSE
            return (mailbox_buffer[1] == MAILBOX_RESPONSE);
	}
    }

    // We should never arrive here, but if we do, return FALSE (invalid message)
    return 0;
}
