#include <iostream>
#include "account.h"
using namespace std;
#pragma once

//class for the money market account subtype
class MoneyMarket : public account
{
private:
	//creating the variables and interest rate specific to the money market account type
	double balance;
	int months;
	const double INT_RATE = 0.0125;
	double withdrawalPenalty;

public:

	//default constructor setting the terms to default values
	MoneyMarket() : account()
	{
		balance = 0;
		months = 0;
		withdrawalPenalty = 0;
		setAccountType(3);
	}

	//overloaded constructor
	MoneyMarket(int accountid, int customerid, int accounttype, double b, int m) : account(accountid, customerid, accounttype)
	{
		this->balance = b;
		this->months = m;
		this->withdrawalPenalty = 0;
	}

	//function that returns the age of the account 
	virtual int getMonths() override
	{
		return months;
	}

	//setter function for the balance of the money market account
	void setBalance(double b)
	{
		balance = b;
	}

	//getter function for the balance of the money market account 
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

	//function that determines the penalty based on the money market account balance
	virtual double getWithdrawalPenalty() override
	{
		//if statement that sets a penalty if the balance is less than $10000
		if (balance < 10000 && months > 0)
		{
			setWithdrawalPenalty(200);
			return 200;
		}
		
		else
		{
			setWithdrawalPenalty(0);
			return 0;
		}
			
	}

	//function that sets the withdrawal penalty amount for the account
	virtual void setWithdrawalPenalty(double pen) override
	{
		withdrawalPenalty = pen;
	}

	//printing function that first calls the account print function, then displays the money market account balance
	virtual void print()
	{
		account::print();
		cout << "Money Market Balance: $" << balance << endl;
	}

	//function that allows the user to deposit money into their money market account
	virtual void deposit(double money) override
	{
		balance += money;
		setBalance(balance);
	}

	//function that handles the withdrawal from the money market account with the penalty obtained from the get withdrawal penalty function
	virtual void withdraw(double money) override
	{
		balance = ((balance)-(money + getWithdrawalPenalty()));
		setBalance(balance);
	}

	//override function that prints only the balance of the money market account
	virtual void printBalance() override
	{
		cout << "Money Market Balance: $" << balance << endl;
	}

};