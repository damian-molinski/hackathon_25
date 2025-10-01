#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

// Initializes the transaction system, clearing any existing balance data.
void init_transactions(void);

// Checks for and processes any new transactions from the input source.
void process_incoming_transactions(void);

// Populates a provided array with the transaction history for a customer.
// returns the number of transactions found.
int get_transactions_for_customer(int customer_id, int* customer_transactions, int max_transactions);

// Calculates and returns the total balance for a given customer.
long get_total_balance_for_customer(int customer_id);

#endif
