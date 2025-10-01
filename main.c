#include <stdio.h>
#include <atari.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <peekpoke.h>

#include "animation.h"
#include "balance_screen.h"
#include "login_screen.h"
#include "transactions.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define MAX_PASSWORD_LEN 15
#define MAX_USER_NUMBER_LEN 15

#define HORIZONTAL_BOX_MARGIN 2

#define MENU_BOX_X HORIZONTAL_BOX_MARGIN
#define MENU_BOX_WIDTH (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN)
#define MENU_BOX_Y 4
#define MENU_BOX_HEIGHT 14

#define USER_NUMBER_DISPLAY_X (MENU_BOX_X + 2)
#define USER_NUMBER_DISPLAY_Y (MENU_BOX_Y + 1)
#define SEPARATOR_Y (MENU_BOX_Y + 2)

#define MENU_TITLE_TEXT "MAIN MENU"
#define MENU_TITLE_TEXT_LEN 9
#define MENU_TITLE_X (MENU_BOX_X + (MENU_BOX_WIDTH - MENU_TITLE_TEXT_LEN) / 2)
#define MENU_TITLE_Y (MENU_BOX_Y + 4)

#define MENU_OPTION_CONTENT_X_OFFSET 2
#define MENU_OPTION1_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION1_Y (MENU_BOX_Y + 6)
#define MENU_OPTION2_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION2_Y (MENU_BOX_Y + 8)
#define MENU_OPTION3_X (MENU_BOX_X + MENU_OPTION_CONTENT_X_OFFSET)
#define MENU_OPTION3_Y (MENU_BOX_Y + 10)

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

extern void draw_box(unsigned char x, unsigned char y, unsigned char width, unsigned char height);

int main(void)
{
    char password[MAX_PASSWORD_LEN + 1];
    char user_number[MAX_USER_NUMBER_LEN + 1];
    char ch;
    unsigned char k;
    int current_selection = 0;
    const int num_menu_options = 3;
    unsigned char keypress;
    int customer_id;

program_start:
    current_selection = 0;
    init_transactions();

    handle_login(user_number, password, MAX_PASSWORD_LEN);
    customer_id = atoi(user_number);

    play_animation();

    // Draw the main menu frame
    clrscr();
    draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);
    gotoxy(USER_NUMBER_DISPLAY_X, USER_NUMBER_DISPLAY_Y);
    cprintf("User: %s", user_number);
    textcolor(COLOR_BLUE);
    gotoxy(MENU_BOX_X + 1, SEPARATOR_Y);
    for (k = 0; k < MENU_BOX_WIDTH - 2; ++k) { cputc(CH_HLINE); }
    textcolor(COLOR_WHITE);
    gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
    cprintf(MENU_TITLE_TEXT);

    POKE(764, 255);
    while (1)
    {
        bgcolor(COLOR_BLACK);
        textcolor(COLOR_WHITE);
        gotoxy(MENU_OPTION1_X, MENU_OPTION1_Y);
        if (current_selection == 0) cprintf("> Balance             "); else cprintf("  Balance             ");
        gotoxy(MENU_OPTION2_X, MENU_OPTION2_Y);
        if (current_selection == 1) cprintf("> Logout              "); else cprintf("  Logout              ");
        gotoxy(MENU_OPTION3_X, MENU_OPTION3_Y);
        if (current_selection == 2) cprintf("> Exit                "); else cprintf("  Exit                ");

        keypress = PEEK(764);
        switch (keypress)
        {
            case 255:
                process_incoming_transactions();
                break;
            case /*CH_CURS_UP*/ 142:
                POKE(764, 255);
                current_selection--;
                if (current_selection < 0) current_selection = num_menu_options - 1;
                break;
            case /*CH_CURS_DOWN*/ 143:
                POKE(764, 255);
                current_selection++;
                if (current_selection >= num_menu_options) current_selection = 0;
                break;
            case /*CH_ENTER*/ 12:
                POKE(764, 255);
                if (current_selection == 0)
                {
                    show_balance_screen(customer_id);

                    // Redraw main menu after returning
                    clrscr();
                    draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
                    bgcolor(COLOR_BLACK);
                    textcolor(COLOR_WHITE);
                    gotoxy(USER_NUMBER_DISPLAY_X, USER_NUMBER_DISPLAY_Y);
                    cprintf("User: %s", user_number);
                    textcolor(COLOR_BLUE);
                    gotoxy(MENU_BOX_X + 1, SEPARATOR_Y);
                    for (k = 0; k < MENU_BOX_WIDTH - 2; ++k) { cputc(CH_HLINE); }
                    textcolor(COLOR_WHITE);
                    gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
                    cprintf(MENU_TITLE_TEXT);
                }
                else if (current_selection == 1)
                {
                    clrscr();
                    goto program_start;
                }
                else if (current_selection == 2)
                {
                    clrscr();
                    draw_box(CONFIRM_BOX_X, CONFIRM_BOX_Y, CONFIRM_BOX_WIDTH, CONFIRM_BOX_HEIGHT);
                    bgcolor(COLOR_BLACK);
                    textcolor(COLOR_WHITE);
                    gotoxy(CONFIRM_MSG_X, CONFIRM_MSG_Y);
                    cprintf(CONFIRM_MSG_TEXT);
                    ch = cgetc();
                    if (ch == 'Y' || ch == 'y')
                    {
                        clrscr();
                        bgcolor(COLOR_BLACK);
                        textcolor(COLOR_WHITE);
                        gotoxy(MSG_X, MSG_Y);
                        cprintf("Exiting program. Goodbye!");
                        return EXIT_SUCCESS;
                    }
                    else
                    {
                        // Redraw main menu
                        clrscr();
                        draw_box(MENU_BOX_X, MENU_BOX_Y, MENU_BOX_WIDTH, MENU_BOX_HEIGHT);
                        bgcolor(COLOR_BLACK);
                        textcolor(COLOR_WHITE);
                        gotoxy(USER_NUMBER_DISPLAY_X, USER_NUMBER_DISPLAY_Y);
                        cprintf("User: %s", user_number);
                        textcolor(COLOR_BLUE);
                        gotoxy(MENU_BOX_X + 1, SEPARATOR_Y);
                        for (k = 0; k < MENU_BOX_WIDTH - 2; ++k) { cputc(CH_HLINE); }
                        textcolor(COLOR_WHITE);
                        gotoxy(MENU_TITLE_X, MENU_TITLE_Y);
                        cprintf(MENU_TITLE_TEXT);
                    }
                }
                break;
        }
        POKE(764, 255);
    }
    return EXIT_SUCCESS;
}
