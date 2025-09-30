#include <atari.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "animation.h"
#include "balance_screen.h"
#include "login_screen.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define MAX_PASSWORD_LEN 15

#define HORIZONTAL_BOX_MARGIN 2

#define MENU_BOX_X HORIZONTAL_BOX_MARGIN
#define MENU_BOX_WIDTH (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN)
#define MENU_BOX_Y 5
#define MENU_BOX_HEIGHT 10
#define MENU_TITLE_TEXT "MAIN MENU"
#define MENU_TITLE_TEXT_LEN 9
#define MENU_TITLE_X (MENU_BOX_X + (MENU_BOX_WIDTH - MENU_TITLE_TEXT_LEN) / 2)
#define MENU_TITLE_Y (MENU_BOX_Y + 1)

#define MENU_OPTION_CONTENT_X_OFFSET 2
#define MENU_OPTION1_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION1_Y (MENU_BOX_Y + 3)
#define MENU_OPTION2_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION2_Y (MENU_BOX_Y + 5)
#define MENU_OPTION3_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION3_Y (MENU_BOX_Y + 7)

#define CONFIRM_BOX_WIDTH 26
#define CONFIRM_BOX_HEIGHT 5
#define CONFIRM_BOX_X ((SCREEN_WIDTH - CONFIRM_BOX_WIDTH) / 2)
#define CONFIRM_BOX_Y ((SCREEN_HEIGHT - CONFIRM_BOX_HEIGHT) / 2)
#define CONFIRM_MSG_TEXT "Are you sure? (Y/N)"
#define CONFIRM_MSG_TEXT_LEN 20
#define CONFIRM_MSG_X (CONFIRM_BOX_X + (CONFIRM_BOX_WIDTH - CONFIRM_MSG_TEXT_LEN) / 2)
#define CONFIRM_MSG_Y (CONFIRM_BOX_Y + 2)

#define MSG_X_MARGIN (SCREEN_WIDTH / 5)
#define MSG_X MSG_X_MARGIN
#define MSG_Y 12

// draw_box is now defined in login_screen.c
extern void draw_box(unsigned char x, unsigned char y, unsigned char width, unsigned char height);

int main(void) {
    char password[MAX_PASSWORD_LEN + 1];
    char ch;
    int current_selection = 0;
    const int num_menu_options = 3;

program_start:
    current_selection = 0;

    handle_login(password, MAX_PASSWORD_LEN);

    play_animation();

    clrscr();
    draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
    bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
    gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
    cprintf(MENU_TITLE_TEXT);

    while (1) {
        bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
        gotoxy(MENU_OPTION1_X, MENU_OPTION1_Y);
        if (current_selection == 0) cprintf("> Balance             "); else cprintf("  Balance             ");
        gotoxy(MENU_OPTION2_X, MENU_OPTION2_Y);
        if (current_selection == 1) cprintf("> Logout              "); else cprintf("  Logout              ");
        gotoxy(MENU_OPTION3_X, MENU_OPTION3_Y);
        if (current_selection == 2) cprintf("> Exit                "); else cprintf("  Exit                ");
        
        ch = cgetc();
        switch (ch) {
            case CH_CURS_UP:
                current_selection--;
                if (current_selection < 0) current_selection = num_menu_options - 1;
                break;
            case CH_CURS_DOWN:
                current_selection++;
                if (current_selection >= num_menu_options) current_selection = 0;
                break;
            case CH_ENTER:
                if (current_selection == 0) {
                    show_balance_screen();
                    
                    clrscr();
                    draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
                    bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
                    gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
                    cprintf(MENU_TITLE_TEXT);
                } else if (current_selection == 1) {
                    clrscr(); goto program_start;
                } else if (current_selection == 2) {
                    clrscr();
                    draw_box(CONFIRM_BOX_X, CONFIRM_BOX_Y, CONFIRM_BOX_WIDTH, CONFIRM_BOX_HEIGHT);
                    bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
                    gotoxy(CONFIRM_MSG_X, CONFIRM_MSG_Y);
                    cprintf(CONFIRM_MSG_TEXT);
                    ch = cgetc();
                    if (ch == 'Y' || ch == 'y') {
                        clrscr();
                        bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
                        gotoxy(MSG_X, MSG_Y);
                        cprintf("Exiting program. Goodbye!");
                        return EXIT_SUCCESS;
                    } else {
                        clrscr();
                        draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
                        bgcolor(COLOR_BLACK); textcolor(COLOR_WHITE);
                        gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
                        cprintf(MENU_TITLE_TEXT);
                    }
                }
                break;
        }
    } 
    return EXIT_SUCCESS;
}
