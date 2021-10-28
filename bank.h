#ifndef _BANK_H_
#define _BANK_H_

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <error.h>
#include <dirent.h>
#include <time.h>

/* Macros */
#define CUSTOMERECORD ".reginfo.db"
#define TEMPFILE ".reginfo.tmp"
#define HISTORY "/var/log/history.log"
#define MAX_LINE 100
#define MONEY_T long double
#define LINESIZE 50

/* Program data */

typedef enum
{
    f_name, l_name, email,
    phone_no, pass, balance
} infoIDs;

typedef enum {R, D, T} trans_t;

/**
 * RegInfo - the data that will be used to register a person
 * @fn: the first name
 * @ln: the last name
 * @email: the email address
 * @phone_no: the phone number of such
 * @pwd: the password
 */
typedef struct
{
    char *fn;
    char *ln;
    char *email; 
    char *phone_no;
    char *pwd;
    MONEY_T balance;
} RegInfo;

/**
 * Task - contains the option given by user and the action to be performed.
 * @op: the option passed by the user
 * @action: the action to be taken
 */
typedef struct
{
    char *op;
    int (*f)(char *);
} Task;

/*=================//My Function Prototypes\\===============*/
/* In login.c */
int create_account(RegInfo *);
int login(char *, char *);

/* In validate.c */
bool isValidEmail(char *email);
bool isValidPhoneNo(char *tele_no);
bool isStrongPassword(char *pwd);

/* In services.c */
MONEY_T deposit(MONEY_T amount, RegInfo *data);
MONEY_T transfer(MONEY_T amount, RegInfo *data);
int updateCustomerBalance(RegInfo *data);
MONEY_T check_balance(MONEY_T amount, RegInfo *data);
MONEY_T view_transaction_history(MONEY_T amount, RegInfo *data);

/* In extractor.c */
int extract_data(int id, RegInfo *data, void (*extractor)(char *, RegInfo *));
void bextractor(char *bal_s, RegInfo *data);
void fnextractor(char *fname, RegInfo *data);
void pwdextractor(char *pwd, RegInfo *data);
void pnextractor(char *pn, RegInfo *data);
void emextractor(char *email, RegInfo *data);
void lnextractor(char *lname, RegInfo *data);

/* In logger.c */
void get_system_time(void);
int document_transaction(int type, RegInfo *data, MONEY_T amount, 
                        void (*custom_logger)(FILE *, RegInfo, MONEY_T));
void transfer_logger(FILE *, RegInfo, MONEY_T);
void deposit_logger(FILE *, RegInfo, MONEY_T);
void signup_logger(FILE *, RegInfo, MONEY_T);

/* In misctools.c */
int copy(char *old_file, char *new_file);
void abrupt_exit(char *, short);
RegInfo create_new_reginfo(char *fn, char *ln, char *email, char *pn, char *pwd);
char *encrypt(char const *);
RegInfo build_reginfo(void);

#endif