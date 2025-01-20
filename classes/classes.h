#ifndef CLASSES_H
#define CLASSES_H
#include "basics.h"
#include "functions.h"

using namespace std;

class BankAccount {
    private:
        int balance;
        int accountNum;
    public:
    BankAccount() {
        this->balance = balance;
        this->accountNum = accountNum;
    } // Har denna o göra med att map behöver en default constructor?

    BankAccount(int balance, int accountNum) {
        this->balance = balance;
        this->accountNum = accountNum;
    }
    BankAccount(int accountNum) {
        this->balance = 0;
        this->accountNum = accountNum;
    }
    
    void deposit(int amount, mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        balance += amount;
    }

    void withdraw(int amount, mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        balance -= amount;
    }

    int getBalance(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return balance;
    }

    int getAccountNum(mutex &funcMtx) {
        lock_guard<mutex> lock(funcMtx);
        return accountNum;
    }

};

class BankManagement {
    private:

    public:
    map<int, BankAccount> accounts;
    map<int, BankAccount>::iterator it = accounts.begin();

    void addBankAccount (int AccountNuminput) {
        accounts[AccountNuminput] = BankAccount(AccountNuminput);
    }
};


#endif