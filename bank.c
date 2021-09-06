#include "bank.h"

int main(void)
{
    // int status;
    // MONEY_T money;
    // char *passwd;
    RegInfo reginfo;
    // char fn[30], ln[30], em[40], pn[12], pwd[50];

    // scanf("%s%s%s%s%s", fn, ln, em, pn, pwd);

    // printf("\n%s\n%s\n%s\n%s\n%s\n", fn, ln, em, pn, pwd);

    // if (isValidPhoneNo(pn))
    //     printf("Valid phone number!\n");
    // else
    //     printf("Error: %s is not valid phone number!\n", pn);

    // if (isValidEmail(em))
    //     printf("Valid Email!\n");
    // else
    //     printf("Error: %s is not valid email!\n", em);
    
    // passwd = encrypt(pwd);
    // if (!passwd)
    // {
    //     puts("Oh! I'm sorry, I couldn't encrypt it!");
    //     return (1);
    // }

    // reginfo = create_new_reginfo(fn, ln, em, pn, passwd);
    // reginfo = build_reginfo();
    // printf("%s %s %s %s %s %.2Lf\n", reginfo.fn, reginfo.ln, reginfo.email,
    //         reginfo.phone_no, reginfo.pwd, reginfo.balance);
    // money = check_balance(120.3, &reginfo);
    // // create_account(&reginfo);
    // // puts(reginfo.pwd);
    // // login(reginfo.email, reginfo.pwd);
    // MONEY_T amount;
    // printf("Enter amount to deposit: ");
    // scanf("%Lf", &amount);

    // // money = deposit(amount, &reginfo);
    // // printf("The new balance is %.2Lf\n", (money != -1) ? money : reginfo.balance);

    // printf("Enter amount to transfer: ");
    // scanf("%Lf", &amount);

    // money = transfer(amount, &reginfo);
    // printf("Your balance is #%.2Lf\n", (money >= 0) ? money : reginfo.balance);
    // status = document_transaction(T, &reginfo, amount, transfer_logger);
    // if (!status)
    //     puts("Successful!");
    // else
    //     puts("Not Successful!");
    // status = document_transaction(D, &reginfo, amount, deposit_logger);
    // if (!status)
    //     puts("Successful!");
    // else
    //     puts("Not Successful!");

    // status = extract_data(pass, &reginfo, pwdextractor);
    // if (!status)
    //     printf("%s\n", reginfo.pwd);
    view_transaction_history(1200, &reginfo);

    return (0);
}
