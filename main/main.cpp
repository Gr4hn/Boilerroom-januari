#include "basics.h"
#include "functions.h"
#include "classes.h"

using namespace std;

mutex mtx, funcMtx, testMtx;
condition_variable cv;
bool ready = false;
bool dataReady = false;


int x;

int main() {
    map<int, BankAccount> accounts;
    //Creates 5 acc with balance first and the key value is the acc number Ex, 111
    BankAccount account1(1000, 111);
    BankAccount account2(2000, 222);
    BankAccount account3(3000, 333);
    BankAccount account4(4000, 444);
    BankAccount account5(5000, 555);
    //Connects each map acc to a specific acc
    accounts[111] = account1;
    accounts[222] = account2;
    accounts[333] = account3; 
    accounts[444] = account4;
    accounts[555] = account5;

    
    cout << "Hello, World!" << endl << endl;
    Sleep(2000);
    system("cls");

    BankAccount CustomerID;
    BankManagement bankManagement;
    vector<thread> threads;

    //Gives every "Costumer" it's own task to do,  
    for (int i = 0; i < 10; i++) {
        BankAccount &CustomerID = AccSelection(mtx, &accounts);
        cout << "Customer " << i + 1 << " is running" << endl;  
            switch (i % 3) {
                case 0: //Deposit money in given acc
                    threads.push_back(thread(Client1, ref(CustomerID), &accounts, ref(funcMtx), ref(mtx), ref(testMtx), ref(cv), ref(ready)));
                    break;
                case 1: //Withdraws money in given acc
                    threads.push_back(thread(Client2, ref(CustomerID), &accounts, ref(funcMtx), ref(mtx), ref(testMtx), ref(cv), ref(ready)));
                    break;
                case 2: //Checks saldo in given acc
                    threads.push_back(thread(Client3, ref(CustomerID), &accounts, ref(funcMtx), ref(mtx), ref(cv), ref(ready), ref(testMtx)));
                    break;
                default: //Error message if acc doesnt exist
                    cout << "Invalid account selection!" << endl;
                    break;
            }
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
    //Gives full rapport of total amount of deposit, withdrawn and the final balance of every acc
    cout << "All threads have finished" << endl << endl
     << "Final account balances: " << endl
     << "Account 111 total withdrawls: " << accounts[111].getTotalWithdrawals() << endl
     << "Account 111 total deposits: " << accounts[111].getTotalDeposits() << endl
     << "Account 111 total balance: " << accounts[111].getBalance() << endl << endl

     << "Account 222 total withdrawls: " << accounts[222].getTotalWithdrawals() << endl
     << "Account 222 total deposits: " << accounts[222].getTotalDeposits() << endl 
     << "Account 222: " << accounts[222].getBalance() << endl << endl

     << "Account 333 total withdrawls: " << accounts[333].getTotalWithdrawals() << endl
     << "Account 333 total deposits: " << accounts[333].getTotalDeposits() << endl
     << "Account 333: " << accounts[333].getBalance() << endl << endl

     << "Account 444 total withdrawls: " << accounts[444].getTotalWithdrawals() << endl
     << "Account 444 total deposits: " << accounts[444].getTotalDeposits() << endl
     << "Account 444: " << accounts[444].getBalance() << endl << endl

     << "Account 555 total withdrawls: " << accounts[555].getTotalWithdrawals() << endl
     << "Account 555 total deposits: " << accounts[555].getTotalDeposits() << endl
     << "Account 555: " << accounts[555].getBalance() << endl << endl; 


    //cin.get();
    return 0;
}