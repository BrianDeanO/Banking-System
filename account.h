#include <iostream>
using namespace std;
#pragma once

class account
{
private:
	int accountID;
	int customerID;
	int accountType;
	//in the public location are all the function prototypes for the account class 
public:

	account();
	account(int accountid, int customerid, int accountType);
	int getAccountID();
	void setAccountID(int id);
	int getCustomerID();
	void setCustomerID(int c);
	int getAccountType();
	void setAccountType(int t);

	//starting the virtual functions which allow for proper use with the derived classes
	//abstract functions are also present and are directly for the special derived classes to make their own
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
	accountType = -1;
}

//overloaded constructor that takes in the account id and the customer id from the customer
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

//set the account id function making sure it is a proper number
void account::setAccountID(int id)
{
	if (id < 0)
		return;
	accountID = id;
}

//function for getting the customer ID member
int account::getCustomerID()
{
	return customerID;
}

//setting the customer ID member
void account::setCustomerID(int c)
{
	if (c < 0)
		return;
	customerID = c;
}

//function for getting the accounttype number
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
