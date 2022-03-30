#pragma once
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "transaction.h"
using namespace std;

//TransactionList class that inherits from priority_queue 
class TransactionList : public priority_queue<transaction>
{
public:

	//function that writes our priority queue list of transactions to a binary file
	void writeFile(string filename)
	{
		int count = this->size();
		ofstream ofs(filename, ios::binary);

		ofs.write((char*)(&count), sizeof(int));

		transaction temp;

		//using a while loop to write each transaction to file while we empty our queue
		while (count != 0)
		{
			temp = this->top();

			ofs.write((char*)(&temp), sizeof(transaction));

			this->pop();

			count--;
		}

		ofs.close();
	}

	//function that reads our binary file of transactions and adds them into our priorty queue list 
	void readFile(string filename)
	{

		transaction temp;
		int count = 0;
		ifstream ifs(filename, ios::binary);

		ifs.read((char*)(&count), sizeof(int));

		//using a for loop to read all of transactions
		for (int i = 0; i < count; i++)
		{
			ifs.read((char*)(&temp), sizeof(transaction));
			this->push(temp);
		}

		ifs.close();
	}

	//function that prints the our transaction list
	void printTList()
	{
		int count = this->size();
		transaction temp;

		//while loop that takes the top object of our queue, prints it, and removes it
		while (count != 0)
		{
			temp = this->top();

			temp.print();

			this->pop();

			count--;
		}
	}

	//function that deletes the transactions tied with a deleted account
	void deleteTransactions(int accID)
	{
		int count = this->size();
		//creating a temporary vector to hold transactions
		vector<transaction> tVect;
		transaction temp;

		//using a for loop to work through our queue of transactions
		for (int i = 0; i < count; i++)
		{
			temp = this->top();

			//if statement that places the non-matching transactions into our vector
			if (temp.getAccID() != accID)
			{
				tVect.push_back(temp);
			}

			this->pop();
		}

		int newCount = tVect.size();

		//for loop that pushes our vector of transactions into our new priority queue of transactions
		for (int c = 0; c < newCount; c++)
		{
			this->push(tVect[c]);
		}

		//with the proper transactions deleted, we write the updated queue to file
		this->writeFile("transactions.dat");
	}

	//function that allows us to delete the transactions that were tied with a customer's accounts
	void deleteCustomerTransactions(int custID)
	{
		int count = this->size();
		//creating a temporary vector to hold transactions
		vector<transaction> tVect;
		transaction temp;

		//using a for loop to work through our queue of transactions
		for (int i = 0; i < count; i++)
		{
			temp = this->top();

			//if statement that places the non-matching transactions into our vector
			if (temp.getCustID() != custID)
			{
				tVect.push_back(temp);
			}

			this->pop();
		}
		
		int newCount = tVect.size();

		//for loop that pushes our vector of transactions into our new priority queue of transactions
		for (int c = 0; c < newCount; c++)
		{
			this->push(tVect[c]);
		}

		//with the proper transactions deleted, we write the updated queue to file
		this->writeFile("transactions.dat");
	}

};

