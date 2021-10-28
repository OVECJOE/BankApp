#include "bank.h"

/**
 * isValidEmail - checks if an email address is valid.
 * @email: the email to validate.
 * 
 * Return: true if valid, else false
 */
bool isValidEmail(char *email_addr)
{
    int i = 0, len;
    char *str;
    char *providers[] = {"gmail", "yahoo", "hotmail", "outlook", NULL};

    if ((str = strchr(email_addr, '@')))
        while (providers[i])
            if (strstr(str, providers[i++]))
            {
                len = strlen(str) - 4;
                if (!strcmp(str + len, ".com"))
                    return (true);
            }

    return (false);
}

/**
 * isValidPhoneNo - checks to ensure phone number is valid
 * @tele_no: a pointer to a Nigeria's format phone number string.
 * 
 * Return: return true if valid, else false
 */
bool isValidPhoneNo(char *tele_no)
{
    size_t i;
    char prefixes[][4] = {"070", "080", "081", "090", "091"};
    char p[4];

    p[3] = '\0';

    if (!tele_no || strlen(tele_no) != 11)
        return (false);

    for (i = 0; i < 3; i++)
        p[i] = tele_no[i];

    for (i = 0; i < strlen(tele_no); i++)
        if (tele_no[i] < 48 || tele_no[i] > 57)
            return (false);

    for (i = 0; prefixes[i]; i++)
        if (!strcmp(prefixes[i], p))
            return (true);

    return (false);
}

/**
 * isStrongPassword - tests the strength of a password
 * @pwd: a pointer to the password string
 * 
 * Return: true if true, else false 
 */
bool isStrongPassword(char *pwd)
{
    int len = strlen(pwd);
    int count;

    if ((len < 8) || (len > 49))
        return (false);

    while (*pwd)
    {
        if (*pwd >= 'A' && *pwd <= 'Z')
            count++;
        if (*pwd >= 48 && *pwd <= 57)
            count++;
    }

    return ((count > 3) ? true : false);
}
