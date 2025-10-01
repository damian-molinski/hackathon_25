#include <atari.h>
#include <conio.h>
#include <string.h>
#include "login_screen.h"

#define CH_DBL_ULCORNER 201
#define CH_DBL_URCORNER 185
#define CH_DBL_LLCORNER 200
#define CH_DBL_LRCORNER 188
#define CH_DBL_HLINE    205
#define CH_DBL_VLINE    186

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define HORIZONTAL_BOX_MARGIN 2

#define INPUT_BOX_X HORIZONTAL_BOX_MARGIN
#define INPUT_BOX_WIDTH (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN)
#define INPUT_BOX_Y 8
#define INPUT_BOX_HEIGHT 8
#define USER_NUM_PROMPT_X (INPUT_BOX_X + 4)
#define USER_NUM_PROMPT_Y (INPUT_BOX_Y + 2)
#define PASSWORD_PROMPT_X (INPUT_BOX_X + 4)
#define PASSWORD_PROMPT_Y (INPUT_BOX_Y + 4)
#define INPUT_FIELD_X (USER_NUM_PROMPT_X + 13)

#define SHADOW_OFFSET_X 2
#define SHADOW_OFFSET_Y 1

void draw_box(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
    unsigned char i, j;

    // 1. Draw the drop shadow first
    bgcolor(COLOR_GRAY1);
    for (i = 0; i < height; ++i) {
        gotoxy(x + SHADOW_OFFSET_X, y + SHADOW_OFFSET_Y + i);
        for (j = 0; j < width; ++j) {
            cputc(' ');
        }
    }

    // 2. Draw the main box on top with double lines
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_BLUE);
    for (i = 0; i < width; ++i) {
        gotoxy(x + i, y); cputc(0x12);
        gotoxy(x + i, y + height - 1); cputc(0x12);
    }
    for (i = 1; i < height - 1; ++i) {
        gotoxy(x, y + i); cputc('|');
        gotoxy(x + width - 1, y + i); cputc('|');
    }
    gotoxy(x, y); cputc(0x11);
    gotoxy(x + width - 1, y); cputc(0x05);
    gotoxy(x, y + height - 1); cputc(0x1a);
    gotoxy(x + width - 1, y + height - 1); cputc(0x03);
    
    // 3. Reset colors for content inside the box
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
}

void get_input(unsigned char y, char* buffer, unsigned char max_len, unsigned char is_password) {
    char ch;
    unsigned char i = 0;
    
    cursor(1);
    gotoxy(INPUT_FIELD_X, y);

    while (i < max_len) {
        ch = cgetc();
        if (ch == CH_ENTER) {
            break;
        }
        if ((ch == CH_DEL || ch == CH_RUBOUT || ch == CH_CURS_LEFT) && i > 0) {
            --i;
            gotoxy(INPUT_FIELD_X + i, y);
            cputc(' ');
            gotoxy(INPUT_FIELD_X + i, y);
        } else if (ch >= ' ' && ch <= '~') {
            buffer[i++] = ch;
            cputc(is_password ? '*' : ch);
        }
    }
    buffer[i] = '\0';
    cursor(0);
}

void handle_login(char* user_number_buffer, char* password_buffer, unsigned char max_len) {
    do {
        clrscr();
        draw_box(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT);
        
        bgcolor(COLOR_BLACK);
        textcolor(COLOR_WHITE);
        
        gotoxy(USER_NUM_PROMPT_X, USER_NUM_PROMPT_Y);
        cprintf("User Number: ");
        
        gotoxy(PASSWORD_PROMPT_X, PASSWORD_PROMPT_Y);
        cprintf("Password:    ");

        get_input(USER_NUM_PROMPT_Y, user_number_buffer, max_len, 0);

        get_input(PASSWORD_PROMPT_Y, password_buffer, max_len, 1);

    } while (strlen(user_number_buffer) == 0 || strlen(password_buffer) == 0);
}
