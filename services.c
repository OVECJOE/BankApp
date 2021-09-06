#include "bank.h"

/**
 * deposit - The deposit money function.
 * @amount: the amount to be deposit
 * @data: A pointer to the customer's data
 * Return: the new balance if successful,
 * else -1.
 */
MONEY_T deposit(MONEY_T amount, RegInfo *data)
{
    int status;

    if (!data)
        return (-1);

    status = extract_data(balance, data, bextractor);
    if (status)
        return (-1);

    if (!amount)
        return (data->balance);

    data->balance += amount;

    status = updateCustomerBalance(data);
    if (status)
        return (-1);

    status = document_transaction(D, data, amount, deposit_logger);
    if (status)
        return (-1);

    return (data->balance);
}

/**
 * transfer - The transact subroutine to deal with transfer transactions.
 * @amount: the amount to be transferred
 * @data: A pointer to the customer's data
 * Return: the customer's balance if successful, else -2 if amount is more than
 * balance, else -1.
 */
MONEY_T transfer(MONEY_T amount, RegInfo *data)
{
    int status;
    MONEY_T bal;

    if (!data)
        return (-1);

    status = extract_data(balance, data, bextractor);
    if (status)
        return (-1);

    bal = data->balance;
    if (bal < amount)
    {
        puts("INSUFFICIENT FUNDS!");
        return (-2);
    }

    bal -= amount;
    data->balance = bal;

    status = updateCustomerBalance(data);
    if (status)
        return (-1);

    status = document_transaction(T, data, amount, transfer_logger);
    if (status)
        return (-1);

    return (data->balance);
}

/**
 * updateCustomerBalance - updates the balance of the customer
 * in the local database.
 * @data: the customer's registration data
 * Return: 0 if successful, else 1
 */
int updateCustomerBalance(RegInfo *data)
{
    int line = 0, status;
    char buffer[LINESIZE];
    FILE *cusInfoFile, *tempFile;

    cusInfoFile = fopen(CUSTOMERECORD, "r");
    tempFile = fopen(TEMPFILE, "w");
    if (!cusInfoFile || !tempFile)
    {
        puts("UNABLE TO COMPLETE TRANSACTION, TRY AGAIN!");
        return (1);
    }

    while ((fgets(buffer, LINESIZE, cusInfoFile) != NULL))
    {
        if (line == 5)
            fprintf(tempFile, "%.2Lf\n", data->balance);
        else
            fputs(buffer, tempFile);

        line++;
    }

    fclose(cusInfoFile);
    fclose(tempFile);

    status = remove(CUSTOMERECORD);
    if (status == -1)
        perror("Remove");

    status = rename(TEMPFILE, CUSTOMERECORD);
    if (status == -1)
        perror("Rename");

    return (0);
}

/**
 * check_balance - Check the balance of the customer
 * @amount: Unused
 * @data: a pointer to the customer's data
 * Return: balance
 */
MONEY_T check_balance(MONEY_T amount, RegInfo *data)
{
    int status;

    (void) amount;
    status = extract_data(balance, data, bextractor);
    if (status)
        abrupt_exit("Operation Could Not Be Completed. Try Again!", -1);
    
    printf("\nYour Balance:\t#%.2Lf\n", data->balance);
    return (data->balance);
}

/**
 * view_transaction_history - prints to the screen the transaction history
 * @amount: Unused
 * @data: Unused
 * Return: 0 if successful, else -1
 */
MONEY_T view_transaction_history(MONEY_T amount, RegInfo *data)
{
    FILE *logfile;
    char *line;
    size_t size;
    ssize_t nread;

    (void) amount;
    (void) data;

    logfile = fopen(HISTORY, "r");
    if (!logfile)
    {
        perror("Error");
        return (-1);
    }

    while ((nread = getline(&line, &size, logfile)) != -1)
        printf("%s", line);
    
    fclose(logfile);
    return (0);
}
