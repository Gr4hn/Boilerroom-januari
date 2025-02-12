#include "basics.h"
#include "classes.h"
#include "functions.h"

//This contains all the functions we are using in the program

//Gets a radom number for depositing and withdrawing to simulate a transaction
int randomBalance () {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 9999);
    return dis(gen);
}
//Gets a random account which constumers uses for transaction or check balance
int randomAccount () {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5);
    return dis(gen);
}

int randomAccountNum () {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    return dis(gen);
}

// Selects a random BankAccount from the map in a thread-safe manner.
// Locks the mutex and returns a random BankAccount reference from the map.
/* BankAccount& AccSelection (mutex &mtx, map<int, BankAccount> *accounts) {
    lock_guard<mutex> lock(mtx);
    switch (randomAccount()) {
        case 1:
            return accounts->at(111);
        case 2:
            return accounts->at(222);
        case 3:
            return accounts->at(333);
        case 4:
            return accounts->at(444);
        case 5:
            return accounts->at(555);
        default:
            cout << "Invalid account selection!" << endl;
            break;
    }
}
 */
//Deposits money
void Client1 (BankAccount &CustomerID, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx, mutex &testMtx, condition_variable &cv, bool &ready) { //deposit
    unique_lock<mutex> lock(mtx);
    cout << "Thread " << this_thread::get_id() << " waiting..." << endl;
    cv.wait(lock, [&]{ return ready; });

    int RB = randomBalance();
    cout << "Client 1 is running" << endl;

    {
        lock_guard<mutex> testLock(testMtx);
        {
            lock_guard<mutex> funcLock(funcMtx);
            CustomerID.deposit(RB);
        }
        CustomerID.logDepoist(RB, CustomerID, funcMtx);
    }

    Sleep(1000);
}
//Withdraws money
void Client2 (BankAccount &CustomerID, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx, mutex &testMtx, condition_variable &cv, bool &ready) { //withdraw
    unique_lock<mutex> lock(mtx);
    cout << "Thread " << this_thread::get_id() << " waiting..." << endl;
    cv.wait(lock, [&]{ return ready; });

    int RB = randomBalance();
    cout << "Client 2 is running" << endl;

    {    
        lock_guard<mutex> testLock(testMtx);
        {
            lock_guard<mutex> funcLock(funcMtx);

            CustomerID.withdraw(RB, *accounts);
        }
        CustomerID.logWithdraw(RB, CustomerID, funcMtx);
    }
    Sleep(1000);
}
//Check balance
void Client3 (BankAccount &CustomerID, map<int, BankAccount> *accounts, mutex &funcMtx, mutex &mtx, condition_variable &cv, bool &ready, mutex &testMtx) {  //check balance
    unique_lock<mutex> lock(mtx);
    cout << "Thread " << this_thread::get_id() << " waiting..." << endl;
    cv.wait(lock, [&]{ return ready; });

    cout << "Client 3 is running" << endl;

    {
        lock_guard<mutex> funcLock(funcMtx);
        cout << "Customer " << this_thread::get_id() << " is checking its balance for account " << CustomerID.getAccountNum() << ": " << CustomerID.getBalance() << endl;
    }
    Sleep(1000);
}