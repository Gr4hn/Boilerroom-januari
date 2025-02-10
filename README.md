# Test Program for Bank Management Simulation

This program is a simulation of a bank management system. The program in its current state creates 5 accounts which are then assigned to a map with unique key-values. The program then creates a simulation of 10 customers (threads) who randomly choose one of the bank accounts in the map. After all customers have been assigned an account, the process of Deposit, Withdrawal, and getBalance begins. After this has run 10 times, the program will join all customers (threads) and then print out the total deposits, withdrawals, and the total sum after these runs for each bank account.

# To Extend

What we have considered extending is the following:
* More parallelism - In the clients, by removing our Sleep() functions and instead using lock.unlock() before they enter their specific scopes and locking with the help of lock_guard().
* Remove unnecessary files - Files that do not serve any purpose should be removed, e.g., classes.cpp & basics.cpp, as they only take up memory that can be utilized by other files. Important for units with limited memory.
* Rename/distribute files - Rename files such as classes.h and functions.h should be renamed/distributed into smaller files to increase the clarity of the program.

# How to compile & run the program

The program is made for WindowsOS. The program has an included tasks.json file that will build the program correctly. 

Compile the program in your desired way and run the program: in "~/boilerroom-januari>" type "./main/main". 


