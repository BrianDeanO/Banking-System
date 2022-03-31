#include <iostream>
#include <cmath>
using namespace std;
#pragma once

//base account class that will be the super class for our account subtypes
class account
{
private:
	int accountID;
	int customerID;
	int accountType;

public:

	//list of function prototypes for the account class
	account();
	account(int accountid, int customerid, int accountType);
	int getAccountID();
	void setAccountID(int id);
	int getCustomerID();
	void setCustomerID(int c);
	int getAccountType();
	void setAccountType(int t);

	//writing the virtual functions and abstract functions 
	// which are then overriden by the each of the special derived account subtype classes
	virtual void print();
	virtual void deposit(double money) = 0;
	virtual void withdraw(double money) = 0;
	virtual void printBalance() = 0;
	virtual double getBalance() = 0;
	virtual double getWithdrawalPenalty() = 0;
	virtual void setWithdrawalPenalty(double penalty) = 0;
	virtual double getInterestEarned() = 0;
	virtual int getMonths() = 0;
};

//default constructor setting the terms to default values
account::account()
{
	accountID = 0;
	customerID = 0;

	//setting the accountType to a default value of -1 as to not correspond to a derived class type
	accountType = -1;
}

//overloaded constructor that takes in the account id, customer id and account type from the customer
account::account(int accountid, int customerid, int accountType)
{
	this->accountID = accountid;
	this->customerID = customerid;
	this->accountType = accountType;
}

//get account id function 
int account::getAccountID()
{
	return accountID;
}

//set the account id function making sure it is an appropriate number
void account::setAccountID(int id)
{
	if (id < 0)
		return;
	accountID = id;
}

//function for getting the customer ID number
int account::getCustomerID()
{
	return customerID;
}

//setting the customer ID number
void account::setCustomerID(int c)
{
	if (c < 0)
		return;
	customerID = c;
}

//function for getting the account type number
int account::getAccountType()
{
	return accountType;
}

//function for setting the account type number
void account::setAccountType(int t)
{
	accountType = t;
}

//print function
void account::print()
{
	cout << endl;
	cout << "Customer ID: " << customerID << endl;
	cout << "Account ID: " << accountID << endl;
}
