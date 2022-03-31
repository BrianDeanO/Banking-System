#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "linkedList.h"
#include "customer.h"
using namespace std;

//customerList class that inherits directly from the LinkedList class 
class CustomerList : public LinkedList<customer>
{
public:

	//function for writing our linked list full of customers to our binary file
	void writeFile(string filename)
	{
		//getting the size of our customer list
		int count = this->getCount();

		//opening and creating our binary file
		ofstream ofs(filename, ios::binary);

		//first writing the count variable to our file
		ofs.write((char*)(&count), sizeof(int));

		//creating our temporary variables for traversal and writing
		node<customer>* temp = head;
		customer ctemp;

		//using a while loop to traverse through our linked list and write each customer to our file
		while (temp != 0)
		{
			ctemp = temp->getData();
			ofs.write((char*)(&ctemp), sizeof(customer));
			temp = temp->getNext();
		}

		//closing the file
		ofs.close();
	}

	//function that reads our binary file and fills our linked list with customers
	void readFile(string filename)
	{
		//creating our temporary customer object and count variable
		customer temp;
		int count = 0;

		//creating and opening our input binary file
		ifstream ifs(filename, ios::binary);

		//reading the count variable from file
		ifs.read((char*)(&count), sizeof(int));

		//reading each customer object from the file and adding it to our linked list
		for (int i = 0; i < count; i++)
		{
			ifs.read((char*)(&temp), sizeof(customer));
			this->addRear(temp);
		}

		//closing the file
		ifs.close();
	}

	//creating the sorting function that sorts the list alphabetically by customer last name
	void sort()
	{
		customer temp;
		char* tName1 = 0;
		char* tName2 = 0;

		//using the bubble sorting method with nested for loops
		for (int i = 0; i < this->getCount(); i++)
		{
			for (int j = 0; j < (this->getCount() - 1); j++)
			{
				//making a copy of our first customer's last name for comparison
				tName1 = this->getAt(j).getlname();

				//using a for loop and toupper function to make the whole name capitalized
				for (int k = 0; k < strlen(tName1); k++)
				{
					tName1[k] = toupper(tName1[k]);
				}

				//making a copy of our second customer's last name for comparison
				tName2 = this->getAt(j + 1).getlname();
				//using a for loop and toupper function to make the whole name capitalized
				for (int k = 0; k < strlen(tName2); k++)
				{
					tName2[k] = toupper(tName2[k]);
				}

				//using the strcmp function with the capitalized last names to determine which is 
				// larger. If tName1 is larger than tName2, the if statement runs and the data between
				// the nodes are swapped in the list
				if (strcmp(tName1, tName2) > 0)
				{
					temp = getAt(j);
					this->setDataAt(j, this->getAt(j + 1));
					this->setDataAt(j + 1, temp);
				}
			}
		}
	}

	//function that returns the data of a customer given a user inputted customer ID
	customer getCustomerData(int ID)
	{
		customer cust;
		customer tempnull;

		node<customer>* temp = head;

		//using a while loop to search through our linked list for the customer ID entered by the user
		while (temp != nullptr)
		{
			cust = temp->getData();

			//returning the current customer object once the ID matches in the linked list
			if (ID == cust.getid())
			{
				return cust;
			}

			else
			{
				temp = temp->getNext();
			}
		}

		//returning a blank customer object if the customer was not found
		return tempnull;
	}

	//function that deletes a customer from our customer linked list
	void deleteCustomer(customer cust)
	{
		customer cTemp;
		int id = cust.getid();
		node<customer>* temp = head;

		//using a for loop to traverse through the linked list of customers 
		for (int i = 0; i < this->count; i++)
		{
			cTemp = temp->getData();

			//removing the customer from our linked list once the ID matches
			if (id == cTemp.getid())
			{
				removeAt(i);
			}
			
			else
			{
				temp = temp->getNext();
			}
		}

		//re-sorting the customer list before writing to file
		this->sort();

		//writing the updated customer list to file
		this->writeFile("customers.dat");
	}
};
