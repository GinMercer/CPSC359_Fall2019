// This program demonstrates how to initialize a frame buffer for a
// 1024 x 768 display, and how to draw on it using a simple checker board
// pattern.

/////////////////////////////////////////////////////////////////////////////////
//
//      Sijia Yin
//      30049836
//
//      CPSC359 Assignment04
//
//      the source for this assignment are from tut DrawingWithCharacterMovement
//
//
//////////////////////////////////////////////////////////////////////////////////



// Included header files
#include "uart.h"
#include "framebuffer.h"

// Moved all the functions that have to do with initializing and reading from the snes
// to this file
#include "snes.h"

#define MAZESIZEY 12
#define MAZESIZEX 16
#define SQUARESIZE 64

#define NUMBUTTONS 6

// A struct to represent a button
struct Button
{
    int number;
    char* name;
};

// A struct to represent a position
struct Point
{
    int x;
    int y;
};

// (0,0) is top left corner
int masterMaze[MAZESIZEX][MAZESIZEY];

void initializeMasterMaze();

void drawSquare(int x, int y, unsigned int colour);
void drawMazeAt(int x, int y);
void drawMaze();

// pseudo constructors for the structs that we have created above
struct Button createButton(int number, char* name);
struct Point createPoint(int x, int y);



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       main
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function initializes the UART terminal and initializes
//                  a frame buffer for a 1024 x 768 display. Each pixel in the
//                  frame buffer is 32 bits in size, which encodes an RGB value
//                  (plus an 8-bit alpha channel that is not used). The program
//                  then draws and displays an 18 x 12 checker board pattern.
//
////////////////////////////////////////////////////////////////////////////////

void main()
{
    unsigned short data, currentState = 0xFFFF;

    // Initialize the UART terminal
    uart_init();

    uart_puts("Hello World!");

    initializeSNES();

    // Initialize the frame buffer
    initFrameBuffer();


    initializeMasterMaze();


    // Create an array of size NUMBUTTONS to hold all the buttons that we are using on the SNES controller
    struct Button buttons[NUMBUTTONS];
    buttons[0] = createButton(3, "Start");
    buttons[1] = createButton(4, "Up");
    buttons[2] = createButton(5, "Down");
    buttons[3] = createButton(6, "Left");
    buttons[4] = createButton(7, "Right");
    buttons[5] = createButton(9, "X");

    // Create a character represented by an x, y position
    struct Point character = createPoint(0, 0);


    drawMaze();

    // Draw the character
    drawSquare(character.x, character.y, GREEN);

    //
    while (1) {
    	// Read data from the SNES controller
    	data = get_SNES();

        // Write out data if the state of the controller has changed
        //if (data != currentState) {

            // Record the state of the controller
            //currentState = data;
            //in order to hold to draw, we need to delete this current

            // If no buttons have been pressed
            if (data == 0)
                continue;

            // Draw the maze at the character's position
            drawMazeAt(character.x, character.y);

            
            for (int i = 0; i < NUMBUTTONS; ++i) {
                if (((1 << buttons[i].number) & data) != 0) {

                    switch (buttons[i].number) {
                        // Start will reset the character's position
                        case 3 :
                        drawMaze();//make it restart from where it stop
                        break;

                        // Up will move the character up they if will still be within bounds
                        case 4 :
                        if (character.y > 0)
                            character.y -= 1;
                        break;

                        // Down will move the character down if they will still be within bounds
                        case 5 :
                        if (character.y < MAZESIZEY - 1)
                            character.y += 1;
                        break;

                        // Left will move the character left if they will still be within bounds
                        case 6 :
                        if (character.x > 0)
                            character.x -= 1;
                        break;

                        // Right will move the character right if they will still be within bounds
                        case 7 :
                        if (character.x < MAZESIZEX - 1)
                            character.x += 1;
                        break;

                        // X 
                        case 9 :
                        uart_puts("Acid Bonus");
                        break;

                        default :
                        break;
                    }
                }
                if (((1 << buttons[0].number) & data) != 0) {}
                else{
                    drawSquare(character.x, character.y, YELLOW);//every move will leave a square
                }
            }

            // Draw the character
            if (((1 << buttons[0].number) & data) != 0) {}
            else{
                drawSquare(character.x, character.y, GREEN);//my pen
            }
        //}
    	
    	// 
    	microsecond_delay(60000);//to make it slower
    }
}



void drawSquare(int x, int y, unsigned int colour)
{
    drawSquareToFrameBuffer(y * SQUARESIZE, x * SQUARESIZE, SQUARESIZE, colour);
}


void drawMazeAt(int x, int y)
{
    switch (masterMaze[x][y]) {
        case 0 :
        drawSquare(x, y, GRAY);
        break;

        case 1 :
        drawSquare(x, y, WHITE);
        break;

        default :
        break;
    }
}


void drawMaze()
{
    for (int i = 0; i < MAZESIZEX; ++i)
        for (int j = 0; j < MAZESIZEY; ++j)
            drawMazeAt(i, j);
}




void initializeMasterMaze()
{
    for (int i = 0; i < MAZESIZEX; ++i) {
        for (int j = 0; j < MAZESIZEY; ++j) {
            masterMaze[i][j] = ((i + j) % 2);
        }
    }
} 


struct Button createButton(int number, char* name)
{
    struct Button b;
    b.number = number;
    b.name = name;
    return b;
}


struct Point createPoint(int x, int y)
{
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

