#include <atari.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "balance_screen.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define HORIZONTAL_BOX_MARGIN 2

#define ACCOUNT_TITLE_TEXT "ACCOUNT DETAILS"
#define ACCOUNT_TITLE_TEXT_LEN 15
#define ACCOUNT_TITLE_X ((SCREEN_WIDTH - ACCOUNT_TITLE_TEXT_LEN) / 2)
#define ACCOUNT_TITLE_Y 2
#define CURRENT_BALANCE_X HORIZONTAL_BOX_MARGIN
#define CURRENT_BALANCE_Y (ACCOUNT_TITLE_Y + 2)
#define SEPARATOR_Y (CURRENT_BALANCE_Y + 2)
#define TABLE_HEADER_Y (SEPARATOR_Y + 1)
#define TABLE_ROW_START_Y (TABLE_HEADER_Y + 1)
#define ID_COL_X HORIZONTAL_BOX_MARGIN
#define TYPE_COL_X (ID_COL_X + 5)
#define AMOUNT_COL_X (TYPE_COL_X + 13)

#define EXIT_PROMPT_X HORIZONTAL_BOX_MARGIN
#define EXIT_PROMPT_Y (SCREEN_HEIGHT - 3)

void show_balance_screen(void) {
    unsigned char k;
    clrscr();
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);

    gotoxy(ACCOUNT_TITLE_X, ACCOUNT_TITLE_Y);
    cprintf(ACCOUNT_TITLE_TEXT);

    textcolor(COLOR_GREEN);
    gotoxy(CURRENT_BALANCE_X, CURRENT_BALANCE_Y);
    cprintf("Current Balance:  10000 CR");

    textcolor(COLOR_BLUE);
    gotoxy(HORIZONTAL_BOX_MARGIN, SEPARATOR_Y);
    for (k = 0; k < (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN); ++k) {
        cputc(CH_HLINE);
    }

    textcolor(COLOR_WHITE);
    gotoxy(ID_COL_X, TABLE_HEADER_Y); cprintf("ID");
    gotoxy(TYPE_COL_X, TABLE_HEADER_Y); cprintf("TYPE");
    gotoxy(AMOUNT_COL_X, TABLE_HEADER_Y); cprintf("AMOUNT");

    gotoxy(ID_COL_X, TABLE_ROW_START_Y); cprintf("001");
    gotoxy(TYPE_COL_X, TABLE_ROW_START_Y); cprintf("Deposit");
    gotoxy(AMOUNT_COL_X, TABLE_ROW_START_Y); cprintf(" +10000 CR");

    gotoxy(ID_COL_X, TABLE_ROW_START_Y + 1); cprintf("002");
    gotoxy(TYPE_COL_X, TABLE_ROW_START_Y + 1); cprintf("Withdrawal");
    gotoxy(AMOUNT_COL_X, TABLE_ROW_START_Y + 1); cprintf("   -500 CR");

    gotoxy(ID_COL_X, TABLE_ROW_START_Y + 2); cprintf("003");
    gotoxy(TYPE_COL_X, TABLE_ROW_START_Y + 2); cprintf("Deposit");
    gotoxy(AMOUNT_COL_X, TABLE_ROW_START_Y + 2); cprintf("  +2000 CR");

    gotoxy(ID_COL_X, TABLE_ROW_START_Y + 3); cprintf("004");
    gotoxy(TYPE_COL_X, TABLE_ROW_START_Y + 3); cprintf("Withdrawal");
    gotoxy(AMOUNT_COL_X, TABLE_ROW_START_Y + 3); cprintf("  -1500 CR");

    textcolor(COLOR_GRAY2);
    gotoxy(EXIT_PROMPT_X, EXIT_PROMPT_Y);
    cprintf("Press any key to return...");
    cgetc();
}
