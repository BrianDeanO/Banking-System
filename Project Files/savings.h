#include <iostream>
#include "account.h"
using namespace std;
#pragma once

class savings : public account
{
private:
	const double INT_RATE = .0105;
	double balance;
	int months;
	double withdrawalPenalty;

public:

	//default constructor setting the terms to default values
	savings() : account() 
	{
		balance = 0;
		months = 0;
		withdrawalPenalty = 0;
		setAccountType(0);
	}

	//second overloaded constructor
	savings(int accountid, int customerid, int accounttype, double b, int m) : account(accountid, customerid, accounttype)
	{
		this->balance = b;
		this->months = m;
		this->withdrawalPenalty = 0;
	}

	virtual int getMonths() override
	{
		return months;
	}

	//function that sets the balance for the savings account
	void setBalance(double b)
	{
		balance = b;
	}

	//getter function for the balance of the savings account with the parameter equal to the amount of months the user has been with the bank
	virtual double getBalance() override
	{
		return balance;
	}

	//function that only returns the interest earned over the months the user has been at the bank
	virtual double getInterestEarned() override
	{
		double temp;
		double interestEarned;
		temp = balance * (pow((1 + (INT_RATE / 12)), months * 12));
		interestEarned = temp - balance;
		return interestEarned;
	}

	//function that determines the penalty based on the savings account balance
	virtual double getWithdrawalPenalty() override
	{

	if (balance < 1000 && months > 0)
	{
		setWithdrawalPenalty(50);
		return 50;
	}

	else
		setWithdrawalPenalty(0);
		return 0;
	}

	//function that sets the withdrawal penalty amount for the account
	virtual void setWithdrawalPenalty(double pen) override
	{
		withdrawalPenalty = pen;
	}

	//printing function that first calls the account print function, then displays the savings account balance
	void print()
	{
		account::print();
		cout << "Savings Account Balance: $" << balance << endl;
	}

	//function that allows the user to deposit money into their savings account
	void deposit(double money) override
	{
		balance += money;
		setBalance(balance);
	}

	//function that handles the withdrawal from the savings account with the penalty obtained from the get withdrawal penalty function
	virtual void withdraw(double money) override
	{

		balance = ((balance)-(money + getWithdrawalPenalty()));
		setBalance(balance);
	}

	//override function that prints only the balance of the savings account
	void printBalance() override
	{
		cout << "Savings Account Balance: $" << balance << endl;
	}

};
