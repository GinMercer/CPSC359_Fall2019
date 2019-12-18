#include "gpio.h"
#include "systimer.h"

// Function prototypes
void initializeSNES();

unsigned short get_SNES();
void init_GPIO9_to_output();
void set_GPIO9();
void clear_GPIO9();
void init_GPIO11_to_output();
void set_GPIO11();
void clear_GPIO11();
void init_GPIO10_to_input();
unsigned int get_GPIO10();
