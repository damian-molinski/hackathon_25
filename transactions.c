#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <peekpoke.h>
#include "transactions.h"

// Private data for the transaction module
static unsigned char *input_file = "H6:IN";
static unsigned char tx_buffer[256];
static unsigned int last_check_timestamp = 0;
static int balances[10][10]; // Max 10 customers, 10 transactions each

// --- Private Helper Functions ---

static unsigned int current_timestamp()
{
    return (PEEK(18) * 65536 + PEEK(19) * 256 + PEEK(20)) / 60;
}

static void read_incoming_transaction()
{
    unsigned int current_time = current_timestamp();
    unsigned int diff = current_time - last_check_timestamp;
    FILE *file;

    if (diff > 5)
    {
        last_check_timestamp = current_time;
        file = fopen(input_file, "r");
        if (file == NULL) {
            tx_buffer[0] = 0;
            return;
        }

        if (fgets(tx_buffer, 256, file) == NULL) {
            tx_buffer[0] = 0;
            fclose(file);
            return;
        }

        fclose(file);

        if (remove(input_file) != 0) {
            tx_buffer[0] = 0;
        }
    }
    else
    {
        tx_buffer[0] = 0;
    }
}

static int next_free_balance_slot(int customer_id)
{
    int tx_idx;
    for (tx_idx = 0; tx_idx < 10; ++tx_idx)
    {
        if (balances[customer_id][tx_idx] == 0)
        {
            break;
        }
    }
    return tx_idx;
}

static void deposit()
{
    char *last_colon = strrchr(tx_buffer, ':');
    int customer_id = tx_buffer[2] - 48;
    int amount = atoi(last_colon + 1);
    int tx_idx = next_free_balance_slot(customer_id);
    if (tx_idx < 10) balances[customer_id][tx_idx] = amount;
}

static void withdraw()
{
    char *last_colon = strrchr(tx_buffer, ':');
    int customer_id = tx_buffer[2] - 48;
    int amount = atoi(last_colon + 1);
    int tx_idx = next_free_balance_slot(customer_id);
    if (tx_idx < 10) balances[customer_id][tx_idx] = -amount;
}

// --- Public Functions ---

void init_transactions(void) {
    memset(balances, 0, sizeof(balances));
}

void process_incoming_transactions(void) {
    read_incoming_transaction();
    if (tx_buffer[0] != 0)
    {
        if (tx_buffer[0] == 'D')
        {
            deposit();
        }
        else if (tx_buffer[0] == 'W')
        {
            withdraw();
        }
    }
}

int get_transactions_for_customer(int customer_id, int* customer_transactions, int max_transactions) {
    int count = 0;
    int i;
    for (i = 0; i < 10 && count < max_transactions; ++i) {
        if (balances[customer_id][i] != 0) {
            customer_transactions[count] = balances[customer_id][i];
            count++;
        }
    }
    return count;
}

long get_total_balance_for_customer(int customer_id) {
    long total = 0;
    int i;
    for (i = 0; i < 10; ++i) {
        total += balances[customer_id][i];
    }
    return total;
}
