#include "basics.h"
#include "functions.h"
#include "classes.h"

using namespace std;

mutex mtx;

int main() {
    map<int, BankAccount> accounts;

    BankAccount account1(1000, 111);
    BankAccount account2(2000, 222);
    BankAccount account3(3000, 333);
    BankAccount account4(4000, 444);
    BankAccount account5(5000, 555);
    
    accounts[111] = account1;
    accounts[222] = account2;
    accounts[333] = account3; // Assign a unique key for account3
    accounts[444] = account4;
    accounts[555] = account5;
    accounts[444] = account4;
    accounts[555] = account5;
    
    cout << "Hello, World!" << endl << endl;
    Sleep(2000);
    system("cls");

    BankAccount account;
    BankManagement bankManagement;
/*  bool accontSelected = false;
    bool running = true; */

    /* AccountSelection(account, &accounts, accontSelected);
    mainMenu(account, &accounts, accontSelected, bankManagement, running); */

    
    // Thread 1
    thread t1(Client1, ref(account1), &accounts, ref(mtx));

    // Thread 2
    thread t2(Client2, ref(account5), &accounts, ref(mtx));

    // Thread 3
    thread t3(Client3, ref(account2), &accounts, ref(mtx));

    // Thread 4
    thread t4(Client2, ref(account4), &accounts, ref(mtx));

    // Thread 5
    thread t5(Client1, ref(account3), &accounts, ref(mtx));

    // Thread 6
    thread t6(Client3, ref(account4), &accounts, ref(mtx));

    // Thread 7
    thread t7(Client1, ref(account1), &accounts, ref(mtx));

    // Thread 8
    thread t8(Client2, ref(account5), &accounts, ref(mtx));

    // Thread 9
    thread t9(Client2, ref(account2), &accounts, ref(mtx));

    // Thread 10
    thread t10(Client3, ref(account3), &accounts, ref(mtx));

 
    t1.join();
    t2.join();
    t3.join();
    t4.join(); 
    t5.join(); 
    t6.join(); 
    t7.join(); 
    t8.join(); 
    t9.join(); 
    t10.join(); 
    
    cout << "Balance of account1: " << account1.getBalance() << endl;
    cout << "Balance of account2: " << account2.getBalance() << endl;
    cout << "Balance of account3: " << account3.getBalance() << endl;
    cout << "Balance of account4: " << account4.getBalance() << endl;
    cout << "Balance of account5: " << account5.getBalance() << endl;
    cin.get();
    return 0;
}