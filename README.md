# Banking System Project

#### Synopsis
This banking system uses binary files to store, track, and update persistent linked lists of customer records, the accounts they create, and their transaction history.
##

#### Main Menu
With the single creation of a bank object in the project’s main class, a menu appears and displays ten options for the user to select. Those options are: 
1. Create Customer 
2. Create Account
3. Deposit
4. Withdrawal
5. Print Customers
6. Print Accounts
7. Print Transactions
8. Delete Customer
9. Delete Account
10. Exit System

#### Inheritance and Derived Account Types
The user can create four unique accounts with the bank: Checking, Savings, Certificate of Deposit, and Money Market. Each account type inherits from the same base class named account and has specific penalties, interest rates, and fields that make them unique in design and size. Instead of creating and storing a class object of the desired account type, the system creates a pointer to the abstract account class. This pointer makes handling the accounts easier and allows the program to use only one linked list to store accounts.

#### Storing and Sorting Customers and Accounts
Inheriting from the LinkedList class found in the LinkedList header file, both the CustomerList and AccountList objects handle their elements and behave like the linked list data structure. In the CustomerList, when any menu action results in an insertion or deletion of a customer record, the list sorts alphabetically according to customer last name. And in the same manner, when an account changes in anyway, the AccountList re-sorts in descending order based on each account's current balance.

#### Creating Transaction Objects
The creation of a transaction object occurs when the user either deposits or withdrawals money from any of their available accounts. If the user incurs a withdrawal penalty, the system creates an additional transaction object to record that penalty. To store these transactions, the TransactionList class inherits from the public priority_queue class. Therefore, the sorting of transactions is done automatically in a first-in-first-out manner.

#### Reading and Writing to File
To save and keep a persistent record of customers, accounts, and transactions, their linked lists are constantly being re-sorted and re-written to separate binary files. More specifically, with each menu action selected by the user, the necessary object files are read, and the lists are re-populated. After the menu activity is complete, the affected lists are re-sorted and re-written to file. While all customer and transaction objects are the same size in memory, the different account types are not. To ensure proper writing to and reading from the binary account file, the AccountList class is equipped with a vector that stores the account type IDs in the same order as the AccountList itself. The save and load functions within the AccountList class utilizes this vector to ensure the correct account types are properly read and written to file.

#### Deleting Customers and Accounts
When deleting a customer record from the system, the user enters the identification number associated with the customer object, which is used to find and delete the customer from the CustomerList object. After deleting the customer record, the customer ID number is used to search for and delete all of the accounts linked with the customer. And finally, completing the customer deletion process is the removal of all of the transactions associated with all of the recently deleted accounts. If the user just wants to delete an account, the deletion process would repeat but only affect the chosen account and its transactions.

##### Additional Documentation
To see and read a more in-depth analysis of how the system and its menu actions work, here is a link to the [Banking Project Write-Up](https://github.com/BrianDeanO/Banking-System/files/8174628/Banking_System_Project_BDean.pdf).
