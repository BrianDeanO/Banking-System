#include <iostream>
#include "account.h"
using namespace std;
#pragma once

//savings account subtype inheriting from the account class
class savings : public account
{
private:
	//creating the interest rate and variables specific to the savings account
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

	// overloaded constructor that also calls upon the base account class overloaded constructor
	savings(int accountid, int customerid, int accounttype, double b, int m) : account(accountid, customerid, accounttype)
	{
		this->balance = b;
		this->months = m;
		this->withdrawalPenalty = 0;
	}

	//overriding the getMonths virtual function to retrieve the age of the account
	virtual int getMonths() override
	{
		return months;
	}

	//function that sets the balance for the savings account
	void setBalance(double b)
	{
		balance = b;
	}

	//getter function for the balance of the savings account
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
	
	//if statement that sets a penalty if the balance is less than $1000 
	if (balance < 1000 && months > 0)
	{
		setWithdrawalPenalty(50);
		return 50;
	}

	//else statement that runs if a penalty is not drawn
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
