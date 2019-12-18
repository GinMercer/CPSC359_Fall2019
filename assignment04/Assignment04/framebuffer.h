void initFrameBuffer();
void displayFrameBuffer();

void drawSquareToFrameBuffer(int rowStart, int columnStart, int squareSize, unsigned int color);


// HTML RGB color codes.  These can be found at:
// https://htmlcolorcodes.com/
#define BLACK     0x00000000
#define WHITE     0x00FFFFFF
#define RED       0x00FF0000
#define LIME      0x0000FF00
#define BLUE      0x000000FF
#define AQUA      0x0000FFFF
#define FUCHSIA   0x00FF00FF
#define YELLOW    0x00FFFF00
#define GRAY      0x00808080
#define MAROON    0x00800000
#define OLIVE     0x00808000
#define GREEN     0x00008000
#define TEAL      0x00008080
#define NAVY      0x00000080
#define PURPLE    0x00800080
#define SILVER    0x00C0C0C0
