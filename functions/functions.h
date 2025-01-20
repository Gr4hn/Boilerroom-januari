#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "basics.h"
#include "classes.h"

class BankAccount; // Forward declaration of BankAccount
class BankManagement; // Forward declaration of BankManagement



//void mainMenu (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected, BankManagement bankManagement, bool &running);
void Client1 (BankAccount &account, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx);
void Client2 (BankAccount &account, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx);
void Client3 (BankAccount &account, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx);
//void AccountSelection (BankAccount &account, map<int, BankAccount> *accounts, bool &accountSelected);
int randomBalance();
int randomAccount ();
BankAccount& AccSelection (mutex &mtx, map<int, BankAccount> *accounts);

#endif 