#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include "linkedList.h"
#include "account.h"
#include "savings.h"
#include "checking.h"
#include "certificateofdeposit.h"
#include "moneymarket.h"

using namespace std;

//AccountList class that inherits from our linked list 
class AccountList : public LinkedList<account*>
{
private:
	string filename;
	vector <int> accountTypes;

public:

	//default constructor
	AccountList()
	{
		filename = "default.dat";
	}

	//overloaded constructor
	AccountList(string filename)
	{
		this->filename = filename;
	}

	//function that sets the name of the file being used in the system
	void setFileName(string filename)
	{
		this->filename = filename;
	}

	//function that uses our linked list to add an account as well as its type to the vector of account types
	void addaccount(account* paccount)
	{
		this->addRear(paccount);
		accountTypes.push_back(paccount->getAccountType());
	}

	//function that deletes an account from the linked list
	void deleteaccount(account* paccount)
	{
		int id = paccount->getAccountID();
		node<account*>* temp = head;

		//using a for loop that traverses through our linked list and deletes the account based on its account ID
		for (int i = 0; i < this->count; i++)
		{
			if (id == temp->getData()->getAccountID())
			{
				removeAt(i);
				accountTypes.erase(accountTypes.begin() + i);
				break;
			}

			//else statement that progresses through linked list and increase the position of our vector iterator
			else
			{
				temp = temp->getNext();
			}
		}
		
		//re-sorting the linked list to make sure it is in descending order 
		this->sort();

		//writing the updated accounts list to file
		this->writeFile();
	}

	//function that deletes the accounts that are tied to a customer class through the customer ID
	void deleteCustomerAccounts(int id)
	{
		node<account*>* temp = head;
		account* aTemp = nullptr;

		int i = 0;

		//using a while loop that enables us to process the entire linked list and delete every account tied with our deleted customer object
		do
		{
			aTemp = getAt(i);

			if (id == aTemp->getCustomerID())
			{
				//removing the account from the list, erasing its account type from the vector, and setting the iterator back to the 
				removeAt(i);
				accountTypes.erase(accountTypes.begin() + i);
			}
			
			else
			{
				i++;
			}

		} while (this->count > i);

		//re-sorting the linked list to make sure it is in descending order 
		this->sort();

		//writing the updated accounts list to file
		this->writeFile();
	}

	//function that prints the information of an account
	void print()
	{
		node<account*>* temp = head;

		while (temp != 0)
		{
			cout << "Account ID: " << temp->getData()->getAccountID() << endl;
			cout << "Customer ID: " << temp->getData()->getCustomerID() << endl;

			int type = temp->getData()->getAccountType();
			double total = temp->getData()->getInterestEarned() + temp->getData()->getBalance();

			cout << "Account Type: ";

			switch (type)
			{
			case 0: 
				cout << "Savings\n";
				break;

			case 1: 
				cout << "Checking\n";
				break;

			case 2: 
				cout << "Certificate Of Deposit\n";
				break;

			case 3: 
				cout << "Money Market\n";
				break;
			}

			cout << "Current Balance: $" << fixed << setprecision(2) << temp->getData()->getBalance() << endl;

			cout << "Balance With Interest After " << temp->getData()->getMonths() << " months: $";
			cout << fixed << setprecision(2) << total << endl;

			cout << endl;

			temp = temp->getNext();
		}
	}

	//function that reads in our list of accounts from a binary file and stores them in a linked list
	void readFile()
	{
		int count = 0;
		int itemp = 0;
		account* acct = nullptr;

		ifstream in(this->filename, ios::binary);
		in.read((char*)&count, sizeof(int));

		for (int i = 0; i < count; i++)
		{
			in.read((char*)&itemp, sizeof(int));
			accountTypes.push_back(itemp);
		}

		node<account*>* temp = head;

		for (int i = 0; i < count; i++)
		{
			switch (accountTypes[i])//0 - Savings, 1 - Checking, 2 - CD, 3 - MoneyMarket
			{

			case 0:
			{
				savings save;
				in.read((char*)&save, sizeof(savings));
				account* sv = new savings(save.getAccountID(), save.getCustomerID(), 0, save.getBalance(), save.getMonths());
				addaccount(sv);
			} 
				break;

			case 1:
			{
				checking check;
				in.read((char*)&check, sizeof(checking));
				account* ch = new checking(check.getAccountID(), check.getCustomerID(), 1, check.getBalance(), check.getMonths());
				addaccount(ch);
			}
				break;

			case 2:
			{
				CertificateOfDeposit CD;
				in.read((char*)&CD, sizeof(CertificateOfDeposit));
				account* cert = new CertificateOfDeposit(CD.getAccountID(), CD.getCustomerID(), 2, CD.getBalance(), CD.getMonths());
				addaccount(cert);
			}
				break;

			case 3:
			{
				MoneyMarket MM;
				in.read((char*)&MM, sizeof(MoneyMarket));
				account* mon = new MoneyMarket(MM.getAccountID(), MM.getCustomerID(), 3, MM.getBalance(), MM.getMonths());
				addaccount(mon);
			}
				break;

			}

		}

		in.close();
	}

	//function that allows us to save our list of accounts to a binary file
	void writeFile()
	{
		ofstream out(this->filename, ios::binary);
		int count = this->count;
		out.write((char*)&count, sizeof(int));//file header amount of accounts in file

		for (int i = 0; i < count; i++)
		{
			out.write((char*)&accountTypes[i], sizeof(int));
		}

		account* acct = nullptr;

		node<account*>* temp = head;

		for (int i = 0; i < count; i++)
		{
			acct = temp->getData();

			switch (accountTypes[i])// 0 - Savings, 1 - Checking, 2 - CD, 3 - MoneyMarket
			{
			case 0:
				out.write((char*)acct, sizeof(savings));
				break;

			case 1:
				out.write((char*)acct, sizeof(checking));
				break;

			case 2:
				out.write((char*)acct, sizeof(CertificateOfDeposit));
				break;

			case 3:
				out.write((char*)acct, sizeof(MoneyMarket));
				break;
			}

			temp = temp->getNext();
		}

		out.close();
	}

	//function that searches through the linked list for an account using an user inputted ID
	account* getAccountData(int ID)
	{
		account* acct = nullptr;

		node<account*>* temp = head;
		int count = 0;

		while (temp != nullptr)
		{
			acct = temp->getData();

			if (ID == temp->getData()->getAccountID())
			{
				return acct;
			}

			else
			{
				temp = temp->getNext();
				count++;
			}
		}

		return nullptr;
	}

	//function that sorts our linked list of account in order from largest balance to smallest balance
	void sort()
	{
		account* acct = nullptr;
		node<account*>* temp = head;

		double amt1;
		double amt2;

		for (int i = 0; i < this->getCount(); i++)
		{
			for (int j = 0; j < (this->getCount() - 1); j++)
			{
				//setting the balances of our two comparison objects
				amt1 = this->getAt(j)->getBalance();
				amt2 = this->getAt(j + 1)->getBalance();

				//if statement that causes the account data to swtich in the list if they aren't in proper order
				if (amt1 < amt2)
				{
					acct = getAt(j);
					this->setDataAt(j, this->getAt(j + 1));
					this->setDataAt(j + 1, acct);
				}
			}
		}

		//clearing the vector of account types to prepare it for refilling types that are in the correct order
		accountTypes.clear();

		////using a for loop to resort the accountypes vector to reflect the correct order of the linked list
		for (int i = 0; i < this->getCount(); i++)
		{
			int type;
			type = this->getAt(i)->getAccountType();
			accountTypes.push_back(type);
		}

	}

};