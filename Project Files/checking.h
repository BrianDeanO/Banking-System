#include <iostream>
#include "account.h"
using namespace std;
#pragma once

//class for the checking account subtype
class checking : public account
{
private:
	//creating the variables and interest rate specific to the checking account
	double balance;
	int months;
	const double INT_RATE = 0.0002;
	double withdrawalPenalty;

public:

	//default constructor setting the terms to default values
	checking() : account()
	{
		balance = 0;
		months = 0;
		withdrawalPenalty = 0;
		setAccountType(1);
	}

	//overloaded constructor
	checking(int accountid, int customerid, int accounttype, double b, int m) : account(accountid, customerid, accounttype)
	{
		this->balance = b;
		this->months = m;
		this->withdrawalPenalty = 0;
	}

	//function that returns the number of months the account will be active
	virtual int getMonths() override
	{
		return months;
	}

	//setter function for the balance of the checking account
	void setBalance(double b)
	{
		balance = b;
	}

	//function that returns the balance of the account
	virtual double getBalance() override
	{
		return balance;
	}

	//function that only returns the interest earned over the months the user has been at the bank
	virtual double getInterestEarned() override
	{
		double temp;
		double interestEarned;
		temp = balance * (pow((1 + (INT_RATE / 12)), (months * 12)));
		interestEarned = temp - balance;
		return interestEarned;
	}

	//printing function that first calls upon the base class print function, then displays the checking balance
	virtual void print()
	{
		account::print();
		cout << "Checking Account Balance: $" << balance << endl;
	}

	//function that allows the user to deposit money into their checking account
	virtual void deposit(double money) override
	{
		balance += money;
		setBalance(balance);
	}

	//virtual function that allows for withdrawals out of the checking account class
	virtual void withdraw(double money) override
	{
		balance -= money;
		setBalance(balance);
	}

	//override function that prints only the balance of the checking account
	virtual void printBalance() override
	{
		cout << "Checking Account Balance: $" << balance << endl;
	}

	//this function only returns zero since the checking account does not have a withdrawal penalty
	virtual double getWithdrawalPenalty() override
	{
		return 0;
	}

	//function that sets the withdrawal penalty amount for the account
	virtual void setWithdrawalPenalty(double pen) override
	{
		withdrawalPenalty = pen;
	}

};
