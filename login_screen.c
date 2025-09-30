#include <atari.h>
#include <conio.h>
#include <string.h>
#include "login_screen.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define HORIZONTAL_BOX_MARGIN 2

#define INPUT_BOX_X HORIZONTAL_BOX_MARGIN
#define INPUT_BOX_WIDTH (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN)
#define INPUT_BOX_Y 8
#define INPUT_BOX_HEIGHT 6
#define INPUT_PROMPT_X (INPUT_BOX_X + 4)
#define INPUT_PROMPT_Y (INPUT_BOX_Y + 2)
#define INPUT_FIELD_X (INPUT_PROMPT_X + 16)

// We need draw_box here, so it is copied from main.c
void draw_box(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
    unsigned char i;
    bgcolor(COLOR_BLACK);
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
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
}

void handle_login(char* password_buffer, unsigned char max_len) {
    char ch;
    unsigned char i = 0;
    unsigned char k;

    clrscr();
    draw_box(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT);
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
    gotoxy(INPUT_PROMPT_X, INPUT_PROMPT_Y);
    cprintf("Enter Password: ");

    gotoxy(INPUT_FIELD_X, INPUT_PROMPT_Y);
    for(k=0; k<max_len; ++k) {
        cputc(' ');
    }
    gotoxy(INPUT_FIELD_X, INPUT_PROMPT_Y);

    while (i < max_len) {
        ch = cgetc();
        if (ch == CH_ENTER) break;
        if ((ch == CH_DEL || ch == CH_RUBOUT || ch == CH_CURS_LEFT) && i > 0) {
            --i;
            gotoxy(INPUT_FIELD_X + i, INPUT_PROMPT_Y); cputc(' ');
            gotoxy(INPUT_FIELD_X + i, INPUT_PROMPT_Y);
        } else if (ch >= ' ' && ch <= '~') {
            password_buffer[i++] = ch; cputc('*');
        }
    }
    password_buffer[i] = '\0';
}
