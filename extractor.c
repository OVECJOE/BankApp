#include "bank.h"

/**
 * extract_data - extract a particular info from the customer's database
 * and assign it to the RegInfo object.
 * @id: the id of the specific element
 * @data: a pointer to the Reginfo element whose data is to be extracted.
 * @extractor: a function pointer to the appropriate action to be performed
 * in other to store the extracted info.
 * Return: 0 if successful, else 1
 */
int extract_data(int id, RegInfo *data, void (*extractor)(char *, RegInfo *))
{
    FILE *fileptr;
    int i = 0;
    size_t size = 0;
    ssize_t nread;
    char *line;

    fileptr = fopen(CUSTOMERECORD, "r");
    if (!fileptr)
    {
        perror("Error");
        return (1);
    }

    while ((nread = getline(&line, &size, fileptr)) != -1)
    {
        line = strtok(line, "\n");
        
        if (i == id)
        {
            extractor(line, data);
            return (0);
        }

        i++;
    }

    return (1);
}

/**
 * bextractor - Extracts the balance from the database into the RegInfo object
 * @bal_s: the balance string extracted
 * @data: a pointer to the customer's data
 * Return: void
 */
void bextractor(char *bal_s, RegInfo *data)
{
    MONEY_T bal;

    bal = (MONEY_T) atof(bal_s);
    data->balance = bal;
}

/**
 * fnextractor - Extracted the first name into a RegInfo object
 * @fname: the first name extracted
 * @data: a pointer to the customer's data
 * Return: void
 */
void fnextractor(char *fname, RegInfo *data)
{
    if (data->fn)
        free(data->fn);

    data->fn = strdup(fname);
}

/**
 * lnextractor - Extracts the last name into a RegInfo object
 * @lname: the last name extracted
 * @data: a pointer to the customer's data
 * Return: void
 */
void lnextractor(char *lname, RegInfo *data)
{
    if (data->ln)
        free(data->ln);
    
    data->ln = strdup(lname);
}

/**
 * emextractor - Extracts the email into a RegInfo object
 * @email: the email address extracted
 * @data: a pointer to the customer's data
 * Return: void
 */
void emextractor(char *email, RegInfo *data)
{
    if (data->email)
        free(data->email);
    
    data->email = strdup(email);
}

/**
 * pnextractor - Extracts the phone number into a RegInfo object
 * @pn: the phone number extracted
 * @data: a pointer to the customer's data
 * Return: void
 */
void pnextractor(char *pn, RegInfo *data)
{
    if (data->phone_no)
        free(data->phone_no);
    
    data->phone_no = strdup(pn);
}

/**
 * pwdextractor - Extracts the password to a RegInfo object
 * @pwd: the extracted password
 * @data: a pointer to the customer's data
 * Return: void
 */
void pwdextractor(char *pwd, RegInfo *data)
{
    if (data->pwd)
        free(data->pwd);
    
    data->pwd = pwd;
}
