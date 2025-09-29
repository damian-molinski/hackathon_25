#include <conio.h>
#include "animation.h"

void play_animation(void) {
    unsigned char i;
    unsigned int j; // Counter for our delay loop
    char spinner[] = {'/', '-', '\\', '|'};

    clrscr();
    textcolor(COLOR_YELLOW);
    gotoxy(15, 12);
    cprintf("Loading...");

    // Loop 30 times to let the spinner run for a bit
    for (i = 0; i < 30; ++i) {
        gotoxy(25, 12); // Position the spinning character
        cputc(spinner[i % 4]); // Cycle through the 4 spinner characters

        // Simple delay loop to slow down the animation
        for (j = 0; j < 500; ++j);
    }
}