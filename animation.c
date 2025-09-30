#include <conio.h>
#include "animation.h"

#define SCREEN_WIDTH 40

#define LOADING_TEXT_X 15
#define LOADING_TEXT_Y 12
#define SPINNER_X 25
#define SPINNER_Y 12

#define PROGRESS_BAR_WIDTH 30
#define PROGRESS_BAR_Y 14
#define PROGRESS_BAR_X_START ((SCREEN_WIDTH - (PROGRESS_BAR_WIDTH + 2)) / 2)
#define PROGRESS_BAR_X_END (PROGRESS_BAR_X_START + PROGRESS_BAR_WIDTH + 1)


void play_animation(void) {
    unsigned char i;
    unsigned int j;
    char spinner[] = {'/', '-', '\\', '|'};

    clrscr();
    textcolor(COLOR_YELLOW);

    gotoxy(LOADING_TEXT_X, LOADING_TEXT_Y);
    cprintf("Loading...");

    gotoxy(PROGRESS_BAR_X_START, PROGRESS_BAR_Y);
    cputc('[');
    gotoxy(PROGRESS_BAR_X_END, PROGRESS_BAR_Y);
    cputc(']');

    for (i = 0; i < PROGRESS_BAR_WIDTH - 1; ++i) {
        gotoxy(SPINNER_X, SPINNER_Y);
        cputc(spinner[i % 4]);

        gotoxy(PROGRESS_BAR_X_START + 1 + i, PROGRESS_BAR_Y);
        cputc('=');

        for (j = 0; j < 500; ++j);
    }
    
    for (j = 0; j < 2000; ++j);
}
