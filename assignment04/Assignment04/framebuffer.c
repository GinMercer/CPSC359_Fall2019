// Needed header files
#include "uart.h"
#include "mailbox.h"

#include "framebuffer.h"

// Frame buffer constants
#define FRAMEBUFFER_WIDTH      1024  // in pixels
#define FRAMEBUFFER_HEIGHT     768   // in pixels
#define FRAMEBUFFER_DEPTH      32    // bits per pixel (4 bytes per pixel)
#define FRAMEBUFFER_ALIGNMENT  4     // framebuffer address preferred alignment
#define VIRTUAL_X_OFFSET       0
#define VIRTUAL_Y_OFFSET       0
#define PIXEL_ORDER_BGR        0     // needed for the above color codes

// Frame buffer global variables
unsigned int frameBufferWidth, frameBufferHeight, frameBufferPitch;
unsigned int frameBufferDepth, frameBufferPixelOrder, frameBufferSize;
unsigned int *frameBuffer;




////////////////////////////////////////////////////////////////////////////////
//
//  Function:       initFrameBuffer
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function uses the mailbox request/response protocol
//                  to allocate and set the frame buffer. This includes the
//                  width, height, and depth of the framebuffer, plus the
//                  desired pixel order (BGR). The mailbox response is used
//                  to set the frame buffer global variables that can be used
//                  later on when drawing to the screen. The most important of
//                  these is the frame buffer address.
//
////////////////////////////////////////////////////////////////////////////////

void initFrameBuffer()
{
    // Initialize the mailbox data structure.
    // It contains a series of tags that specify the
    // desired settings for the frame buffer.
    mailbox_buffer[0] = 35 * 4;
    mailbox_buffer[1] = MAILBOX_REQUEST;

    mailbox_buffer[2] = TAG_SET_PHYSICAL_WIDTH_HEIGHT;
    mailbox_buffer[3] = 8;
    mailbox_buffer[4] = 0;
    mailbox_buffer[5] = FRAMEBUFFER_WIDTH;
    mailbox_buffer[6] = FRAMEBUFFER_HEIGHT;

    mailbox_buffer[7] = TAG_SET_VIRTUAL_WIDTH_HEIGHT;
    mailbox_buffer[8] = 8;
    mailbox_buffer[9] = 0;
    mailbox_buffer[10] = FRAMEBUFFER_WIDTH;
    mailbox_buffer[11] = FRAMEBUFFER_HEIGHT;
    
    mailbox_buffer[12] = TAG_SET_VIRTUAL_OFFSET;
    mailbox_buffer[13] = 8;
    mailbox_buffer[14] = 0;
    mailbox_buffer[15] = VIRTUAL_X_OFFSET;
    mailbox_buffer[16] = VIRTUAL_Y_OFFSET;
    
    mailbox_buffer[17] = TAG_SET_DEPTH;
    mailbox_buffer[18] = 4;
    mailbox_buffer[19] = 0;
    mailbox_buffer[20] = FRAMEBUFFER_DEPTH;

    mailbox_buffer[21] = TAG_SET_PIXEL_ORDER;
    mailbox_buffer[22] = 4;
    mailbox_buffer[23] = 0;
    mailbox_buffer[24] = PIXEL_ORDER_BGR;

    mailbox_buffer[25] = TAG_ALLOCATE_BUFFER;
    mailbox_buffer[26] = 8;
    mailbox_buffer[27] = 0;
    // Request: alignment; Response: frame buffer address 
    mailbox_buffer[28] = FRAMEBUFFER_ALIGNMENT;
    mailbox_buffer[29] = 0;    // Response: Frame buffer size

    mailbox_buffer[30] = TAG_GET_PITCH;
    mailbox_buffer[31] = 4;
    mailbox_buffer[32] = 0;
    mailbox_buffer[33] = 0;    // Response: Pitch

    mailbox_buffer[34] = TAG_LAST;


    // Make a mailbox request using the above mailbox data structure
    if (mailbox_query(CHANNEL_PROPERTY_TAGS_ARMTOVC)) {
	// If here, the query succeeded, and we can check the response

	// Get the returned frame buffer address, masking out 2 upper bits
    mailbox_buffer[28] &= 0x3FFFFFFF;
    frameBuffer = (void *)((unsigned long)mailbox_buffer[28]);

	// Read the frame buffer settings from the mailbox buffer
    frameBufferWidth = mailbox_buffer[5];
    frameBufferHeight = mailbox_buffer[6];
    frameBufferPitch = mailbox_buffer[33];
	frameBufferDepth = mailbox_buffer[20];
	frameBufferPixelOrder = mailbox_buffer[24];
	frameBufferSize = mailbox_buffer[29];

	// Display frame buffer settings to the terminal
	uart_puts("Frame buffer settings:\n");

	uart_puts("    width:       0x");
	uart_puthex(frameBufferWidth);
	uart_puts(" pixels\n");

	uart_puts("    height:      0x");
	uart_puthex(frameBufferHeight);
	uart_puts(" pixels\n");

	uart_puts("    pitch:       0x");
	uart_puthex(frameBufferPitch);
	uart_puts(" bytes per row\n");

	uart_puts("    depth:       0x");
	uart_puthex(frameBufferDepth);
	uart_puts(" bits per pixel\n");

	uart_puts("    pixel order: 0x");
	uart_puthex(frameBufferPixelOrder);
	uart_puts(" (0=BGR, 1=RGB)\n");

	uart_puts("    address:     0x");
	uart_puthex(mailbox_buffer[28]);
	uart_puts("\n");

	uart_puts("    size:        0x");
	uart_puthex(frameBufferSize);
	uart_puts(" bytes\n");
	
    } else {
        uart_puts("Cannot initialize frame buffer\n");
    }
}



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       drawSquare
//
//  Arguments:      rowStart:        Top left pixel y coordinate
//                  columnStart:     Top left pixel x coordinate
//                  squareSize:      Square size in pixels per side
//                  color:           RGB color code
//
//  Returns:        void
//
//  Description:    This function function draws a single square into the
//                  frame buffer. The top left pixel of the square is given,
//                  and it is drawn downwards and to the right on the display.
//                  The size of the square is given in terms of pixels per side,
//                  and the pixels in the square are given the same specified
//                  color.
//
////////////////////////////////////////////////////////////////////////////////

void drawSquareToFrameBuffer(int rowStart, int columnStart, int squareSize, unsigned int color)
{
    int row, column, rowEnd, columnEnd;
    unsigned int *pixel = frameBuffer;


    // Calculate where the row and columns end
    rowEnd = rowStart + squareSize;
    columnEnd = columnStart + squareSize;

    // Draw the square row by row, from the top down
    for (row = rowStart; row < rowEnd; row++) {
	    // Draw each pixel in the row from left to right
        for (column = columnStart; column < columnEnd; column++) {
            // Draw the individual pixel by setting its
            // RGB value in the frame buffer
            pixel[(row * frameBufferWidth) + column] = color;
        }
    }
}



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       drawCheckerboard
//
//  Arguments:      numberOfRows:        Number of checker board rows
//                  numberOfColumns:     Number of checker board columns
//                  squareSize:          Size of the square in pixels per side
//                  color1:              Color of the first square
//                  color2:              The alternating square color
//
//  Returns:        vois
//
//  Description:    This function draws a checkerboard pattern on the display
//                  with the prescribed numbers of rows and columns and the
//                  specified square size. The pattern alternates between the
//                  two specified colors.
//
////////////////////////////////////////////////////////////////////////////////

void drawCheckerboard(int numberOfRows, int numberOfColumns, int squareSize,
		       unsigned int color1, unsigned int color2)
{
    int i, j;

    // Draw the rows from the top down
    for (i = 0; i < numberOfRows; i++) {
        // Draw the squares for the evenly numbered rows
        if ((i % 2) == 0) {
            // Draw alternating squares starting with the first color
            for (j = 0; j < numberOfColumns; j += 2) {
                drawSquareToFrameBuffer(i * squareSize, j * squareSize, squareSize, color1);
                drawSquareToFrameBuffer(i * squareSize, (j + 1) * squareSize, squareSize, color2);
            }
        }
        // Draw the squares for the oddly numbered rows
        else {
            // Draw alternating squares starting with the second color
            for (j = 0; j < numberOfColumns; j += 2) {
            drawSquareToFrameBuffer(i * squareSize, j * squareSize, squareSize, color2);
            drawSquareToFrameBuffer(i * squareSize, (j + 1) * squareSize, squareSize, color1);
            }
        }
    }	    
}



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       displayFrameBuffer
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function displays a checker board pattern, where each
//                  square is 64 x 64 pixels in size. Since the screen
//                  resolution is set to 1024 x 768, the board has 18 x 12
//                  squares in total.
//
////////////////////////////////////////////////////////////////////////////////

void displayFrameBuffer()
{
    int squareSize, numberOfRows, numberOfColumns;


    // Set the size of a checker board square in terms of pixels per side. It
    // should be a number that is a power of 2, so that it can fit cleanly into
    // a 1024 x 768 frame buffer.
    squareSize = 64;

    // Calculate the number of rows and columns
    numberOfRows = frameBufferHeight / squareSize;
    numberOfColumns = frameBufferWidth / squareSize;
 
    // Draw a checker board pattern on the screen
    drawCheckerboard(numberOfRows, numberOfColumns, squareSize, MAROON, GRAY);
}
