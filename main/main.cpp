#include "basics.h"
#include "functions.h"
#include "classes.h"

using namespace std;

mutex mtx;

int main() {
    BankAccount account1(1000, 111);
    BankAccount account2(2000, 222);
/*  BankAccount account3(3000, 333);
    BankAccount account4(4000, 444);
    BankAccount account5(5000, 555); */

    
    map<int, BankAccount> accounts;
    accounts[111] = account1;
    accounts[222] = account2;
/*  accounts[3] = account3; // Assign a unique key for account3
    accounts[4] = account4;
    accounts[5] = account5; */

    cout << "Hello, World!" << endl << endl;
    Sleep(2000);
    system("cls");

    BankAccount account;
    BankManagement bankManagement;
    bool accontSelected = false;
    bool running = true;

    AccountSelection(account, &accounts, accontSelected);
    mainMenu(account, &accounts, accontSelected, bankManagement, running);

    
/*     //Thread 1
     thread t1 ([&account1, &accounts]() {
        mtx.lock();
        cout << "Thread 1 is running" << endl;
        Client1(account1, &accounts);
        mtx.unlock();
    }); */

    //Thread 2
/*     thread t2 ([&account2, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 2 is running" << endl;
        Client2(account2, &accounts);
        mtx.unlock();
    }); */

/*     thread t3 ([&account3, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 3 is running" << endl;
        Client2(account3, &accounts);
        mtx.unlock();
    });
    thread t4 ([&account4, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 4 is running" << endl;
        Client2(account4, &accounts);
        mtx.unlock();
    });
    thread t5 ([&account5, &accounts]() {
        this_thread::sleep_for(chrono::seconds(2));
        mtx.lock();
        cout << "Thread 5 is running" << endl;
        Client2(account5, &accounts);
        mtx.unlock();
    }); */

 
/*     t1.join(); */
/*  t2.join(); */
/*  t3.join();
    t4.join();
    t5.join(); */


    return 0;
}