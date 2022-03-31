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
		//getting the size of the queue
		int count = this->size();

		//opening our file for writing
		ofstream ofs(filename, ios::binary);

		//writing the size of the queue to file
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
		//creating our temporary variables
		transaction temp;
		int count = 0;

		//opening our file for reading
		ifstream ifs(filename, ios::binary);

		//reading in the integer that holds the count data
		ifs.read((char*)(&count), sizeof(int));

		//using a for loop to read all of the transactions from file
		for (int i = 0; i < count; i++)
		{
			ifs.read((char*)(&temp), sizeof(transaction));
			this->push(temp);
		}

		ifs.close();
	}

	//function that prints the contents of each transaction in the list
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

		//using a for loop to work through our queue of transactions, placing the transactions
		// that are not associated with the deleted account into a seperate vector container
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

		//getting the new count of our stored transactions
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

		//using a for loop to work through our queue of transactions, placing the transactions
		// that are not associated with the deleted customer record into a seperate vector container
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
		
		//getting the new count of our saved transactions
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

