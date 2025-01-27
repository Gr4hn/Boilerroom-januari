#include "basics.h"
#include "functions.h"
#include "classes.h"

using namespace std;

mutex mtx, funcMtx, testMtx;
condition_variable cv;
bool ready = false;


int main() {
    map<int, BankAccount> accounts;

    BankAccount account1(1000, 111);
    BankAccount account2(2000, 222);
/*     BankAccount account3(3000, 333);
    BankAccount account4(4000, 444);
    BankAccount account5(5000, 555); */
    
    accounts[111] = account1;
    accounts[222] = account2;
  /*   accounts[333] = account3; 
    accounts[444] = account4;
    accounts[555] = account5; */

    
    cout << "Hello, World!" << endl << endl;
    Sleep(2000);
    system("cls");

    BankAccount account;
    BankManagement bankManagement;
    vector<thread> threads;
/*  bool accontSelected = false;
    bool running = true; */

    /* AccountSelection(account, &accounts, accontSelected);
    mainMenu(account, &accounts, accontSelected, bankManagement, running); */


    for (int i = 1; i < 11; i++) {
        BankAccount &account = AccSelection(mtx, &accounts);
        cout << "Customer " << i + 1 << " is running" << endl;
        //for (auto& [key, value] : accounts) {
            switch (i % 3) {
                case 0:
                    threads.push_back(thread(Client1, ref(account), &accounts, ref(funcMtx), ref(mtx), ref(testMtx), ref(cv), ref(ready)));
                    break;
                case 1:
                    threads.push_back(thread(Client2, ref(account), &accounts, ref(funcMtx), ref(mtx), ref(testMtx), ref(cv), ref(ready)));
                    break;
                case 2:
                    threads.push_back(thread(Client3, ref(account), &accounts, ref(funcMtx), ref(mtx), ref(cv), ref(ready)));
                    break;
                default:
                    throw runtime_error("Invalid account selection!");
                    break;
            }
        //}
        Sleep(500);
    }

    {
        lock_guard<mutex> lock(mtx);
        ready = true;
    }

    cv.notify_all();
    
    
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        } 
    }
    
    cout << "All threads have finished" << endl;
    cout << "Final account balances: " << endl;
    cout << "Account 111 total withdrawls: " << accounts[111].getTotalWithdrawals(funcMtx) << endl;
    cout << "Account 111 total deposits: " << accounts[111].getTotalDeposits(funcMtx) << endl;
    cout << "Account 111 total balance: " << accounts[111].getBalance(funcMtx) << endl;
    cout << "Account 222: " << accounts[222].getBalance(funcMtx) << endl;
    cout << "Account 333: " << accounts[333].getBalance(funcMtx) << endl;
    cout << "Account 444: " << accounts[444].getBalance(funcMtx) << endl;
    cout << "Account 555: " << accounts[555].getBalance(funcMtx) << endl;


    //cin.get();
    return 0;
}