#include "bank.h"

/**
 * copy - copy a file to another
 * @old_file: the file's content to be copied
 * @new_file: the new file to hold the content
 * 
 * Return: 0 if successful, else 1
 */
int copy(char *old_file, char *new_file)
{
    int c;
    FILE *oldptr;
    FILE *newptr;

    oldptr = fopen(old_file, "r");
    if (!oldptr)
        return (1);
    
    newptr = fopen(new_file, "w");
    if (!newptr)
    {
        fclose(oldptr);
        return (1);
    }

    while ((c = fgetc(oldptr)) != EOF)
        fputc(c, newptr);
    
    fclose(oldptr);
    fclose(newptr);

    return (0);
}

/**
 * abrupt_exit - Error handling function
 * Return: nothing
 */
void abrupt_exit(char *errstr, short errcode)
{
    fprintf(stderr, "Error: %s\n", errstr);
    _exit(errcode);
}

/**
 * encrypt - encrypt a string (obviously password)
 * @pd: the password string
 *
 * Return: the hashed string
 */
char *encrypt(char const *pd)
{
    int i = 0, size;
    char c, *hashedStr;

    if (!pd)
        return (NULL);
    
    size = strlen(pd) + 1;
    hashedStr = (char *) malloc(sizeof(char) * size);
    if (!hashedStr)
        return (NULL);
    while (*pd)
    {
        c = ((*pd++ ^ (i << 2)) % 26) + 'a';
        hashedStr[i++] = c;
    }
    hashedStr[i] = '\0';

    return (hashedStr);
}

/**
 * create_new_reginfo - creates a new struct to store registration info.
 * @fn: first name
 * @ln: last name
 * @email: email address
 * @pn: phone number
 * @pwd: password
 * 
 * Return: returns a pointer to RegInfo object
 */
RegInfo create_new_reginfo(char *fn, char *ln, char *email, char *pn, char *pwd)
{
    RegInfo n;

    n.fn = strdup(fn);
    n.ln = strdup(ln);
    n.email = strdup(email);
    n.phone_no = strdup(pn);
    n.pwd = strdup(pwd);
    n.balance = 0.0;

    return (n);
}

RegInfo build_reginfo(void)
{
    RegInfo data;

    extract_data(f_name, &data, fnextractor);
    extract_data(l_name, &data, lnextractor);
    extract_data(email, &data, emextractor);
    extract_data(phone_no, &data, pnextractor);
    extract_data(pass, &data, pwdextractor);
    extract_data(balance, &data, bextractor);

    return (data);
}