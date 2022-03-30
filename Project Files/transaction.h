#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>

class transaction
{
public:
	time_t timestamp;
	int accountID;
	int customerID; 
	int transactionType; //1 - debit(deposit)   2 - credit(withdraw)  3- withdraw penalty
	double amount;

	//default constructor
	transaction()
	{
		timestamp = 0;
		accountID = 0;
		customerID = 0;
		transactionType = 0;
		amount = 0;
	}

	//overloaded constructor taking in the user entered account ID and customer ID and transaction type
	transaction(int accID, int custID, int type, double amt)
	{
		this->accountID = accID;
		this->customerID = custID;
		this->transactionType = type;
		this->amount = amt;
		timestamp = time(NULL);
	}

	//function that sets the account ID for the specific transaction
	void setAccID(int aID)
	{
		this->accountID = aID;
	}
	
	//function that returns the account ID tied to this transaction
	int getAccID()
	{
		return accountID;
	}

	//setter function for the customer ID 
	void setCustID(int cID)
	{
		this->customerID = cID;
	}

	//function that returns the customer ID tied with the transaction
	int getCustID()
	{
		return customerID;
	}

	//setter function for the transaction type
	void setType(int t)
	{
		this->transactionType = t;
	}

	//setter function for the amount that is withdrawn or deposited
	void setAmount(double a)
	{
		this->amount = a;
	}

	//function that returns the amount handled in the transaction
	double getAmount()
	{
		return amount;
	}

	//function that sets the timestamp of a transaction to the current epoch value
	void setTimestamp()
	{
		timestamp = time(NULL);
	}

	//function that handles both deposit and withdrawal transactions
	void makeTransaction(account* acc, int type)
	{
		//setting the transaction's data members with the account that is being processed
		setAccID(acc->getAccountID());
		setCustID(acc->getCustomerID());
		setType(type);
		double amount;

		cout << "Current Balance: $" << acc->getBalance() << endl;
		
		//if statement that runs the process of depositing money into an account
		if (type == 1)
		{
			cout << "How much would you like to deposit? $";
			cin >> amount;

			while (amount < 0)
			{
				cout << "Incorrect Amount. Try Again. How much would you like to withdrawal? $";
				cin >> amount;
			}

			acc->deposit(amount);

			cout << "Updated Balance Amount: $" << acc->getBalance() << endl;

			setAmount(amount);
			setTimestamp();
		}

		//else if statement that allows the user to withdrawal appropriate funds from an account
		else if (type == 2)
		{
			
			cout << "How much would you like to withdrawal? $";
			cin >> amount;

			//a while statement that checks that the user is not withdrawing more than the account has
			while (amount > acc->getBalance() || (amount + acc->getWithdrawalPenalty()) > acc->getBalance() )
			{
				cout << "Insufficient Funds. Try Again. How much would you like to withdrawal? $";
				cin >> amount;
			}

			//validating that the user is entering a positive dollar amount
			while (amount < 0)
			{
				cout << "Negative Dollar Amount. Try Again. How much would you like to withdrawal? $";
				cin >> amount;
			}

			//using the accounts withdraw method with the amount entered by the user
			acc->withdraw(amount);

			cout << "Updated Balance Amount: $" << acc->getBalance() << endl;

			//setting the user entered amount to the transaction object's amount
			setAmount(amount);
			//setting the epoch value of this transaction
			setTimestamp();
		}
	}

	//function that creates a transaction object if the user ended up receiving a withdrawal penalty
	void withdrawalPenaltyTransaction(account* acc, int type)
	{
		//setting the account ID, customer ID, and type of the transaction object
		setAccID(acc->getAccountID());
		setCustID(acc->getCustomerID());
		setType(type);

		//setting the amount of the transaction equal to the withdrawal penalty that the user got
		setAmount(acc->getWithdrawalPenalty());

		//setting the time stamp that this object was created, which should be the same time as the real transaction occured
		setTimestamp();
	}

	//printing function for our transaction object
	void print()
	{
		//using the ctime_s ctime function to change the transactions epoch timestamp into an actual date for output
		char output[26];
		ctime_s(output, sizeof(output), &timestamp);

		cout << "Date: " << output;
		cout << "Customer ID: " << customerID << endl;
		cout << "Account ID: " << accountID << endl;
		cout << "Transaction Type: ";

		//using an if else if statement to properly display the transaction based on its type
		if (transactionType == 1)
		{
			cout << "Deposit\n";
			cout << "Amount: $" << amount << endl;
		}
		else if (transactionType == 2)
		{
			cout << "Withdrawal\n";
			cout << "Amount: $" << amount << endl;
		}
		else if (transactionType == 3)
		{
			cout << "Withdrawal Penalty\n";
			cout << "Amount: $" << amount << endl;
		}


		cout << endl;
	}

	
};

//overloaded < operator that helps with sorting our priority queue by each transaction's epoch value
bool operator<(const transaction& first, const transaction& other)
{
	if (first.timestamp > other.timestamp)
	{
		return true;
	}
	return false;
}

//struct that overloads the parenthesis operator when comparing object timestamp values
struct CompareTime
{
	//this function would automatically run
	bool operator()(transaction const& p1, transaction const& p2)
	{
		//return true if p1 is ordered
		//before p2, for example:

		return p1.timestamp < p2.timestamp;
	}
};