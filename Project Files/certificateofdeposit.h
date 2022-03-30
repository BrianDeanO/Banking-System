#include <iostream>
#include "account.h"
using namespace std;
#pragma once

class CertificateOfDeposit : public account
{
private:
	double balance;
	double intRate;
	int months;
	double withdrawalPenalty;

public:

	//default constructor setting the terms to default values
	CertificateOfDeposit() : account()
	{
		balance = 0;
		intRate = 0;
		months = 0;
		withdrawalPenalty = 0;
		setAccountType(2);
	}

	//second overloaded constructor
	CertificateOfDeposit(int accountid, int customerid, int accounttype, double b, int m) : account(accountid, customerid, accounttype)
	{
		this->balance = b;
		this->months = m;
		this->intRate = getIntRate(m);
		this->withdrawalPenalty = 0;
	}

	virtual int getMonths() override
	{
		return months;
	}

	//function that sets the interest rate based on the amount of months the user has been with the bank
	double getIntRate(int m)
	{
		if (m < 3)
		{
			return 0.0;
		}
		else if (m >= 3 && m < 6)
		{
			return 0.025;
		}
		else if (m >= 6 && m < 12)
		{
			return 0.03;
		}
		else if (m >= 12)
		{
			return 0.05;
		}
	}

	//function that only returns the interest earned over the months the user has been at the bank
	virtual double getInterestEarned() override
	{
		double temp;
		double interestEarned;
		temp = balance * (pow((1 + (intRate / 12)), months * 12));
		interestEarned = temp - balance;
		return interestEarned;
	}

	//setter function for the CD account balance
	void setBalance(double b)
	{
		balance = b;
	}

	//getter function for the balance of the CD account with the parameter equal to the amount of months the user has been with the bank
	virtual double getBalance() override
	{
		return balance;
	}

	//function that determines the penalty based on the amount of months the user has been with the bank
	virtual double getWithdrawalPenalty() override
	{
		double penalty;

		if (months <= 0)
		{
			//setting the penalty variable equal to proper penalty amount
			penalty = (balance * 0);

			//setting the account's withdrawal penalty member to that penalty
			setWithdrawalPenalty(penalty);

			//returing the penalty amount 
			return penalty;
		}

		else if (months < 3 && months >= 1)
		{
			penalty = (balance * .10);
			setWithdrawalPenalty(penalty);
			return penalty;
		}

		else if (months < 6 && months >= 3)
		{
			penalty = (balance * .20);
			setWithdrawalPenalty(penalty);
			return penalty;
		}

		else if (months < 12 && months >= 6)
		{
			penalty = (balance * .50);
			setWithdrawalPenalty(penalty);
			return penalty;
		}

		else if (months >= 12)
		{
			penalty = (balance * 0);
			setWithdrawalPenalty(penalty);
			return penalty;
		}
	}

	//function that sets the withdrawal penalty amount for the account
	virtual void setWithdrawalPenalty(double pen) override
	{
		withdrawalPenalty = pen;
	}

	//virtual function that coincides with the account print function
	virtual void print()
	{
		account::print();
		cout << "Certificate Of Deposit Balance: $" << balance << endl;
	}

	//function that allows the user to deposit money into their CD account
	virtual void deposit(double money) override
	{
		balance += money;
		setBalance(balance);
	}

	//virtual withdraw function that asks the user for the amount of months which will allow for proper penalties to take effect
	virtual void withdraw(double money) override
	{
		balance = ((balance)-(money + getWithdrawalPenalty()));
		setBalance(balance);
	}

	//override function that prints only the balance of the Certificate Of Deposit account
	virtual void printBalance() override
	{
		cout << "Certificate Of Deposit Balance: $" << balance << endl;
	}

};
