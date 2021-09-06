#include "bank.h"

char *trans_types[] = {
    "Registration",
    "Deposit",
    "Transfer",
    NULL
};

/**
 * get_system_time - Gets the date and time from the system and stores it in a file.
 * Return: void
 */
void get_system_time(void)
{
    FILE *histfile;
    struct tm *cal;
    time_t t;

    t = time(NULL);
    cal = localtime(&t);
    if (!cal)
        abrupt_exit("Error: Couldn't obtain system time!", 1);
    
    histfile = fopen(HISTORY, "a+");
    if (!histfile)
    {
        perror("Error");
        return;
    }

    fprintf(histfile, "\t%s", asctime(cal));
    fputs("\t--------------------------\n", histfile);
    fclose(histfile);
}
/**
 * document_transaction -  It documents each transaction made in a file
 * @type: the type of transaction
 * @data: A pointer to the customer's info
 * @amount: the amount he transfer from his account or deposited to his account
 * Return: 0 if successful, else 1
 */
int document_transaction(int type, RegInfo *data, MONEY_T amount, 
                        void (*custom_logger)(FILE *, RegInfo, MONEY_T))
{
    char *trans_type;
    int len = 0;
    FILE *histfile;

    while (trans_types[len])
        len++;

    if (type < 0 || type >= len)
        return (1);
    
    trans_type = trans_types[type];

    histfile = fopen(HISTORY, "a+");
    if (!histfile)
    {
        perror("Error");
        return (1);
    }

    get_system_time();
    fprintf(histfile,"======== %s: ========\n", trans_type);
    custom_logger(histfile, *data, amount);

    fclose(histfile);
    return (0);
}

/**
 * transfer_writer - logs a transfer operation.
 * @file: the log file
 * @data: a customer's data
 * @amount: the amount transferred from account
 * Return: void
 */
void transfer_logger(FILE *file, RegInfo data, MONEY_T amount)
{
    if (!file || !amount)
        return;

    fprintf(file, "|=> %s %s Transferred #%.2Lf From Balance.\n\n",
    data.fn, data.ln, amount);
}

/**
 * deposit_writer - logs a deposit operation
 * @file: the log file
 * @data: the customer's data
 * @amount: the amount deposited to account
 * Return: void
 */
void deposit_logger(FILE *file, RegInfo data, MONEY_T amount)
{
    if (!file || !amount)
        return;
    
    fprintf(file, "|=> %s %s Deposited #%.2Lf To Account.\n\n",
    data.fn, data.ln, amount);
}

/**
 * signup_writer - logs a message if SignUp is successful
 * @file: the log file
 * @data: the customer's data
 * @amount: Unused
 * Return: void
 */
void signup_logger(FILE *file, RegInfo data, MONEY_T amount)
{
    (void) amount;

    if (!file || !amount)
        return;
    
    fprintf(file, "|=> %s %s Successfully Registered!\n\n",
    data.fn, data.ln);
}
