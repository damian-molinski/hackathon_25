#include <stdio.h>
#include <atari.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "balance_screen.h"
#include "transactions.h"

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

void show_balance_screen(int customer_id)
{
    unsigned char k;
    int i;
    long total_balance;
    int transactions[10];
    int num_transactions;

    clrscr();
    bgcolor(COLOR_BLACK);
    textcolor(COLOR_WHITE);

    gotoxy(ACCOUNT_TITLE_X, ACCOUNT_TITLE_Y);
    cprintf(ACCOUNT_TITLE_TEXT);

    // Get and display the total balance
    total_balance = get_total_balance_for_customer(customer_id);
    textcolor(COLOR_GREEN);
    gotoxy(CURRENT_BALANCE_X, CURRENT_BALANCE_Y);
    cprintf("Current Balance: %ld", total_balance);

    textcolor(COLOR_BLUE);
    gotoxy(HORIZONTAL_BOX_MARGIN, SEPARATOR_Y);
    for (k = 0; k < (SCREEN_WIDTH - 2 * HORIZONTAL_BOX_MARGIN); ++k)
    {
        cputc(CH_HLINE);
    }

    textcolor(COLOR_WHITE);
    gotoxy(ID_COL_X, TABLE_HEADER_Y);
    cprintf("ID");
    gotoxy(TYPE_COL_X, TABLE_HEADER_Y);
    cprintf("TYPE");
    gotoxy(AMOUNT_COL_X, TABLE_HEADER_Y);
    cprintf("AMOUNT ($)");

    // Get and display the list of transactions
    num_transactions = get_transactions_for_customer(customer_id, transactions, 10);
    for (i = 0; i < num_transactions; ++i)
    {
        int amount = transactions[i];
        char transaction_type[11];

        if (amount >= 0) {
            strcpy(transaction_type, "Deposit");
            textcolor(COLOR_GREEN);
        } else {
            strcpy(transaction_type, "Withdrawal");
            textcolor(COLOR_RED);
        }

        gotoxy(ID_COL_X, TABLE_ROW_START_Y + i);
        cprintf("%03d", i + 1);

        gotoxy(TYPE_COL_X, TABLE_ROW_START_Y + i);
        cprintf("%s", transaction_type);

        gotoxy(AMOUNT_COL_X, TABLE_ROW_START_Y + i);
        if (amount >= 0)
        {
            cprintf("+%d", amount);
        }
        else
        {
            cprintf("%d", amount);
        }
    }

    textcolor(COLOR_GRAY2);
    gotoxy(EXIT_PROMPT_X, EXIT_PROMPT_Y);
    cprintf("Press any key to return...");
    cgetc();
}
