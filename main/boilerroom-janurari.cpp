#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <ctime>

using namespace std;

mutex mtx, classMTx;

class BankAccount {
    private:
        int balance;
    public:
        BankAccount() {
             this->balance = balance;
        } // Har denna o göra med att map behöver en default constructor?
    
        BankAccount(int balance) {
            this->balance = balance;
           
        }
    
    void deposit(int amount) {
            lock_guard<mutex> lock(classMTx);
            balance += amount;
        }
    void withdraw(int amount) {
            lock_guard<mutex> lock(classMTx);
            balance -= amount;
        }
    int getBalance() {
            lock_guard<mutex> lock(classMTx);
            return balance;
        }
};

class BankManagement {
    private:

    public:
        map<int, BankAccount> accounts;
/*         BankManagement(int accountNumber, BankAccount account) {
            accounts[accountNumber] = account;
        } */

       map<int, BankAccount>::iterator it = accounts.begin();
};

int randomBalance () {
    srand(time(NULL));
    int random = rand() % 1000 + 45;
    return random;
}

int randomAccontNumber () {
/*     int random0 = 0;
    int random1 = 0;
    int random[1];
    srand(time(NULL));
    for (int i = 0; i < 1; i++) {
        random[i] = rand() % 10000 + 45;
        if (random[i] == random[1]) {
            random1 = random[i];
        } else {
            random0 = random[i];
        }
    } */
    srand(time(NULL));
    int random1 = rand() % 10000 + 45;
    int random2 = random1 + rand() % 10000 + 45; 
    int first = random1;
    int second;
    do {
        second = random2;
    } while (second == first);

    return first, second;
/*     return random1; */
}

void Client1 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 1 is running" << endl;
    {
        lock_guard<mutex> lock(mtx);
        cout << account.getBalance() << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    {
        lock_guard<mutex> lock(mtx);
        account.deposit(randomBalance());
        cout << "Client 1 has deposited to account : " << accounts->begin()->first << ". Current balance: " << account.getBalance() << endl;

    }
    this_thread::sleep_for(chrono::milliseconds(500));
    {
        lock_guard<mutex> lock(mtx);
        account.withdraw(randomBalance());
        cout << "Client 1 has withdrawn from account: " << accounts->begin()->first << ". Current balance: " << account.getBalance() << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

/* void Client2 (BankAccount &account, map<int, BankAccount> *accounts) {
    cout << "Client 2 is running" << endl; 
    {
        lock_guard<mutex> lock(mtx);
        cout << account.getBalance() << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    account.deposit(randomBalance());
    cout << "Client 2 has deposited to account : " << accounts->begin()->first << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    account.withdraw(randomBalance());
    cout << "Client 2 has withdrawn from account : " << accounts->begin()->first << ". Current balance: " << account.getBalance() << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
} */




int main() {
    cout << "Hello, World!" << endl;

    BankAccount account1(1000);
    BankAccount account2(2000);
    BankAccount account3(3000);
/*     BankAccount account4(4000);
    BankAccount account5(5000); */

    cout << "Account 1 balance: " << account1.getBalance() << endl;

    
    map<int, BankAccount> accounts;
    
    accounts[1] = account1;
    accounts[2] = account2;
    accounts[3] = account3; // Assign a unique key for account3
    
    //Thread 1
    thread t1 ([&account1, &accounts]() {
        //mtx.lock();
        cout << "Thread 1 is running" << endl;
        Client1(account1, &accounts);
        //mtx.unlock();
    });

    //Thread 2
    thread t2 ([&account2, &accounts]() {
        //this_thread::sleep_for(chrono::seconds(2));
        //mtx.lock();
        cout << "Thread 2 is running" << endl;
        Client1(account2, &accounts);
        //mtx.unlock();
    });



    t1.join();
    t2.join();
    return 0;
}