#include "bank.h"

/**
 * create_account - create an account for new users
 * 
 * @c: a pointer to the struct that holds the user
 * important details
 * Return: status code of 0 if success,
 * 0 if c is NULL, 1 if open sys call fail and
 * 2 if account exists already.
 */
int create_account(RegInfo *c)
{
    DIR *dir;
    struct dirent *file;
    int i, len = 0;
    FILE *fpointer;

    if (!c)
        return (-1);

    char *creds[] = {
        c->fn, c->ln, c->email,
        c->phone_no, c->pwd, NULL};

    while (creds[len])
        len++;

    dir = opendir(".");
    if (!dir)
        abrupt_exit("Unable to read directory", 1);

    while ((file = readdir(dir)))
        if (!strcmp(file->d_name, CUSTOMERECORD))
            abrupt_exit("You already have an account, login", 2);

    closedir(dir);

    fpointer = fopen(CUSTOMERECORD, "w");
    if (!fpointer)
        abrupt_exit("Failed! Try again!\n", 1);

    for (i = 0; i < len; i++)
        fprintf(fpointer, "%s\n", creds[i]);

    fprintf(fpointer, "%.2Lf\n", c->balance);

    fclose(fpointer);
    return (0);
}


/**
 * login - the login subroutine
 * @email: The email address
 * @password: password
 * Return: 0 if success, 1 if account is not found,
 * -1 if email or password is incorrect.
 */
int login(char *email, char *password)
{
    char line[MAX_LINE], *result;
    FILE *stream;

    (void) password;

    stream = fopen(CUSTOMERECORD, "r");
    if (!stream)
        abrupt_exit("You don't have an account with us. Create one!", 1);

    while ((result = fgets(line, MAX_LINE, stream)))
    {
        result = strtok(result, "\n");
        if (!strcmp(result, email))
        {
            while ((result = fgets(line, MAX_LINE, stream)))
            {
                result = strtok(result, "\n");
                if (!strcmp(password, result))
                {
                    printf("Login Successful!\n");
                    return (0);
                }
            }
            puts("Incorrect Password!");
            return (-1);
        }
    }
    fclose(stream);

    puts("Incorrect Email!");
    return (-1);
}
