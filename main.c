#include <atari.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "animation.h"

#define MAX_USERNAME_LEN 15

// The draw_box function remains here
void draw_box(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
    // ... (code for draw_box is unchanged)
    unsigned char i;
    
    textcolor(COLOR_BLUE);
    for (i = 0; i < width; ++i) {
        gotoxy(x + i, y); cputc(CH_HLINE);
        gotoxy(x + i, y + height - 1); cputc(CH_HLINE);
    }
    for (i = 1; i < height - 1; ++i) {
        gotoxy(x, y + i); cputc(CH_VLINE);
        gotoxy(x + width - 1, y + i); cputc(CH_VLINE);
    }
    gotoxy(x, y); cputc(CH_ULCORNER);
    gotoxy(x + width - 1, y); cputc(CH_URCORNER);
    gotoxy(x, y + height - 1); cputc(CH_LLCORNER);
    gotoxy(x + width - 1, y + height - 1); cputc(CH_LRCORNER);
}

// The play_animation function has been REMOVED from this file

int main(void) {
    char username[MAX_USERNAME_LEN + 1];
    char ch;
    unsigned char i = 0;

    // --- Setup the initial UI screen ---
    clrscr();
    draw_box(4, 8, 32, 6);
    textcolor(COLOR_WHITE);
    gotoxy(8, 11);
    cprintf("Enter Username: ");

    // --- Get user input ---
    while (i < MAX_USERNAME_LEN) {
        ch = cgetc();
        if (ch == CH_ENTER) {
            break;
        }
        if (ch == CH_DEL && i > 0) {
            --i;
            cputc(CH_DEL);
        } else if (ch >= ' ' && ch <= '~') {
            username[i++] = ch;
            cputc(ch);
        }
    }
    username[i] = '\0';

    play_animation();

    // --- Display the final result ---
    clrscr();
    textcolor(COLOR_GREEN);
    gotoxy(12, 12);
    cprintf("Welcome, %s!", username);
    
    gotoxy(8, 20);
    textcolor(COLOR_GRAY2);
    cprintf("Press any key to exit.");

    cgetc();

    return EXIT_SUCCESS;
}