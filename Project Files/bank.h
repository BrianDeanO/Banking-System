#pragma once
#include <iostream>
#include <string>
#include "CustomerList.h"
#include "TransactionList.h"
#include "AccountList.h"
using namespace std;


class bank
{
private:
	//lists for all of customers, accounts, and transaction objects
	CustomerList customers;
	AccountList accounts;
	TransactionList transactions;

public:

	//default constructor that automatically calls our banking menu until the user exits the system
	bank()
	{
		//setting the account list file name so we can read and write properly
		accounts.setFileName("accounts.dat");

		int userInput;
		do
		{
			cout << "\n";
			cout << "1. Create Customer\n";
			cout << "2. Create Account\n";
			cout << "3. Deposit\n";
			cout << "4. Withdrawal\n";
			cout << "5. Print Customers\n";
			cout << "6. Print Accounts\n";
			cout << "7. Print Transactions\n";
			cout << "8. Delete Customer\n";
			cout << "9. Delete Account\n";
			cout << "10. Exit System\n";
			cout << "\n What would you like to do? (1-10): ";
			cin >> userInput;
			cin.ignore();

			while (userInput > 10 || userInput < 1)
			{
				cout << "Enter a valid action (1-10):";
				cin >> userInput;
			}

			if (userInput != 10)
			{
				switch (userInput)
				{
				case 1: createCustomer();
					break;
				case 2: createAccount();
					break;
				case 3: menuDeposit();
					break;
				case 4: menuWithdrawal();
					break;
				case 5: printCustomers();
					break;
				case 6: printAccounts();
					break;
				case 7: printTransactions();
					break;
				case 8: deleteCustomer();
					break;
				case 9: deleteAccount();
					break;
				}
			}

			else if (userInput == 10)
			{
				goodbye();
			}

		} while (userInput != 10);

	}

	//function that allows us to add a customer to our linked list
	void createCustomer()
	{
		customer temp;
		int ID;
		string firstName, lastName;

		//reading the customer file if the current list is empty
		if (customers.getCount() == 0)
		{
			customers.readFile("customers.dat");
		}

		//getting user input for the customer object
		cout << "Enter First Name: ";
		cin >> firstName;
		temp.setfname(firstName);
		cout << "Enter Last Name: ";
		cin >> lastName;
		temp.setlname(lastName);
		cout << "Enter Customer ID: ";
		cin >> ID;
		temp.setid(ID);

		//adding the customer object to the back of the linked list
		customers.addRear(temp);

		//sorting the customers by last name before writing them to file
		customers.sort();

		//writing the customer list to file
		customers.writeFile("customers.dat");
	}

	//funcion that creates an account
	void createAccount()
	{
		int type, accID, custID, months;
		double balance;

		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}

		//getting user input and validating that it is correct
		cout << "Enter your exisiting Customer ID: ";
		cin >> custID;

		cout << "What account are you making? (0-Savings, 1-Checking, 2-Certificate Of Deposit, 3-Money Market): ";
		cin >> type;

		if (type < 0 || type > 3)
		{
			cout << "Please enter a valid account type number: ";
			cin >> type;
		}

		cout << "Enter An Account ID: ";
		cin >> accID;

		cout << "Enter a starting balance amount: $";
		cin >> balance;

		cout << "How many months will keep this account active? ";
		cin >> months;

		//creating and adding the accounts to our linked list depending on the account type chosen by the user
		switch (type)
		{

		case 0:
		{
			account* temp = new savings(accID, custID, type, balance, months);
			accounts.addaccount(temp);
		}
			break;

		case 1:
		{
			account* temp = new checking(accID, custID, type, balance, months);
			accounts.addaccount(temp);
		}
			break;

		case 2:
		{
			account* temp = new CertificateOfDeposit(accID, custID, type, balance, months);
			accounts.addaccount(temp);
		}
			break;

		case 3:
		{
			account* temp = new MoneyMarket(accID, custID, type, balance, months);
			accounts.addaccount(temp);
		}
			break;

		}

		//sorting the accounts then writing to file
		accounts.sort();
		accounts.writeFile();
	}

	//function that handles when the user wants to make a deposit to their account
	void menuDeposit()
	{
		transaction temp;
		account* aTemp = nullptr;
		account* aTemp2 = nullptr;
		int accNum;
		int count = 0;

		//if statements that will read the data from the account and transaction files to fill their lists if they aren't already filled
		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}
		if (transactions.size() == 0)
		{
			transactions.readFile("transactions.dat");
		}

		cout << "What is the Account ID? ";
		cin >> accNum;
		
		//using the getAccountData function to set the temporary pointer data to the account based on the user inputted ID
		aTemp = accounts.getAccountData(accNum);

		if (aTemp == nullptr)
		{
			cout << "That Account ID is not in our system.\n";
		}

		else
		{
			//using the makeTransaction function to process the deposit and return a transaction object reflecting the action
			temp.makeTransaction(aTemp, 1);
			transactions.push(temp);
		}

		//setting a temporary account to the beginning of our linked list of accounts
		aTemp2 = accounts.getAt(count);

		//using a while to loop to make the count variable equal the index of the account that was just updated
		while (aTemp2->getAccountID() != accNum)
		{
			count++;
			aTemp2 = accounts.getAt(count);
		}

		//replacing the account in the proper index with its updated form after making its transaction
		accounts.setDataAt(count, aTemp);

		//writing the transaction list to file
		transactions.writeFile("transactions.dat");

		//sorting our accounts list with the updated account in the list
		accounts.sort();
		//writing the now sorted account list to file
		accounts.writeFile();
	}

	//function that processes the withdrawal action 
	void menuWithdrawal()
	{
		transaction temp;
		transaction wTemp;
		account* aTemp = nullptr;
		account* aTemp2 = nullptr;
		int accNum;
		int count = 0;

		//if statements that will read the data from the accounts and transaction files if their lists aren't filled yet
		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}
		if (transactions.size() == 0)
		{
			transactions.readFile("transactions.dat");
		}

		cout << "What is the Account ID? ";
		cin >> accNum;

		//using the getAccountData function to set the temporary pointer data to the account based on the user inputted ID
		aTemp = accounts.getAccountData(accNum);

		//signaling that the account doesn't exist if the account ID's don't match
		if (aTemp == nullptr)
		{
			cout << "That Account ID is not in our system.\n";
		}

		else
		{
			temp.makeTransaction(aTemp, 2);

			//putting the newly created transaction object onto our priority queue of transactions
			transactions.push(temp);

			//if statement that creates a transaction object if the account drew a withdrawal penalty
			if (aTemp->getWithdrawalPenalty() > 0)
			{
				wTemp.withdrawalPenaltyTransaction(aTemp, 3);
				transactions.push(wTemp);
			}
		}

		transactions.writeFile("transactions.dat");

		//setting a temporary account to the beginning of our linked list of accounts
		aTemp2 = accounts.getAt(count);

		//using a while to loop to make the count variable equal the index of the account that was just updated
		while (aTemp2->getAccountID() != accNum)
		{
			count++;
			aTemp2 = accounts.getAt(count);
		}

		//replacing the account in the proper index with its updated form after making its transaction
		accounts.setDataAt(count, aTemp);

		//sorting our accounts list with the updated account in the list
		accounts.sort();
		//writing the now sorted account list to file
		accounts.writeFile();
	}

	//function that prints our complete list of customers
	void printCustomers()
	{
		if (customers.getCount() == 0)
		{
			customers.readFile("customers.dat");
		}

		//if else statement that prints the correct output depending on if the customer list is populated
		if (customers.getCount() == 0)
		{
			cout << "There are no current customers on file.\n";
		}
		else
		{
			//printing the header for this printing function
			cout << "Printing Customers..." << endl;
			cout << "------------------------------------\n";

			//printing the customers
			customers.print();
		}
		
	}
	 
	//function that lets us print the accounts from our linked list of accounts
	void printAccounts()
	{
		//reading the file if the current list of accounts is empty
		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}

		//if else statement that prints the correct output depending on if the accounts list is populated
		if (accounts.getCount() == 0)
		{
			cout << "There are no current accounts on file.\n";
		}
		else
		{
			cout << "Printing Accounts..." << endl;
			cout << "------------------------------------\n";
			accounts.print();
		}

		
	}

	//function that prints the queue of transactions in order from earliest to latest depending on their timestamp
	void printTransactions()
	{
		if (transactions.size() == 0)
		{
			transactions.readFile("transactions.dat");
		}

		//if else statement that prints the correct output depending on if there are any transactions in the queue
		if (transactions.size() == 0)
		{
			cout << "There are no current transactions on file.\n";
		}
		else
		{
			cout << "Printing Transactions..." << endl;
			cout << "------------------------------------\n";
			transactions.printTList();
		}


	}

	//function that allows us to delete a customer as well as all of the accounts the customer is associated with
	void deleteCustomer()
	{
		customer temp;
		int userInput;

		//filling the customer, account and transaction lists if they aren't already full
		if (customers.getCount() == 0)
		{
			customers.readFile("customers.dat");
		}

		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}

		if (transactions.size() == 0)
		{
			transactions.readFile("transactions.dat");
		}

		//getting the user's customer ID
		cout << "What is the Customer ID of the customer you are deleting? ";
		cin >> userInput;

		//getting the data of the customer being deleted and putting it to our temporary customer object
		temp = customers.getCustomerData(userInput);

		//displaying a message on screen if the customer was not found in our search
		if (temp.getid() == 0)
		{
			cout << "That Customer ID is not in our system.\n";
		}

		else
		{
			//deleting the customer from the linked list of customers
			customers.deleteCustomer(temp);

			//now deleting all of the accounts that the customer had on file with the bank, if there are accounts in the list
			if (accounts.getCount() > 0)
			{
				accounts.deleteCustomerAccounts(userInput);
			}

			//deleting the transactions tied with the customer's account, if there are any transactions in the queue
			if (transactions.size() > 0)
			{
				transactions.deleteCustomerTransactions(userInput);
			}

			cout << "Customer Info, Accounts, and Transactions tied with Customer " << userInput << " have been deleted." << endl;
		}
		
		
	}

	//function that allows us to delete an account based on an user inputted ID
	void deleteAccount()
	{
		account* aTemp = nullptr;
		int userInput;

		//reading account and transaction files if they haven't been filled with information yet
		if (accounts.getCount() == 0)
		{
			accounts.readFile();
		}
		if (transactions.size() == 0)
		{
			transactions.readFile("transactions.dat");
		}

		cout << "What is the Account ID of the account you are deleting? ";
		cin >> userInput;

		//getting the data of the account based on the ID entered
		aTemp = accounts.getAccountData(userInput);

		if (aTemp == nullptr)
		{
			cout << "That Account ID is not in our system.\n";
		}

		else
		{
			//using the deleteaccount account list function to delete the account from our linked list of accounts
			accounts.deleteaccount(aTemp);
			transactions.deleteTransactions(userInput);
			cout << "Account " << userInput << " has been deleted." << endl;
		}

		
	}

	//goodbye function that ends the program when the user is finished
	int goodbye()
	{
		cout << "Thanks for doing business with SameDiff bank.\n";
		return 0;
	}
};
