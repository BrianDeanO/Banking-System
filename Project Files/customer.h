#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include "account.h"
using namespace std;
int const SIZE = 50;

class customer
{
private:
	char firstName[SIZE];
	char lastName[SIZE];
	int ID;

public:
	customer();
	customer(int id, char* fname, char* lname);
	customer(int id, string fname, string lname);
	void setid(int id);
	int getid();
	void setfname(char* fname);
	void setfname(string fname);
	char* getfname();
	void setlname(char* lname);
	void setlname(string lname);
	char* getlname();
	void print();
};

//default constructor that sets a customer account equal to nothing
customer::customer()
{
	strcpy_s(firstName, " ");
	strcpy_s(lastName, " ");
	ID = 0;
}

//the two following constructors allow for two different forms of the first name
customer::customer(int id, char* fname, char* lname)
{
	setid(id);
	setfname(fname);
	setlname(lname);
}
customer::customer(int id, string fname, string lname)
{
	setid(id);
	setfname(fname);
	setlname(lname);
}

//below are the setting and getting id functions
void customer::setid(int id)
{
	this->ID = id;
}
int customer::getid()
{
	return ID;
}

//the two following set name functions are for the two different overloaded constructor parameters
void customer::setfname(char* fname)
{
	if (strlen(fname) < 100)
		return;
	strcpy_s(firstName, fname);
}
void customer::setfname(string fname)
{
	if (fname.length() > 100)
		return;
	strcpy_s(firstName, fname.c_str());

}

//get name function that uses char as a universal way of getting the name correctly
char* customer::getfname()
{
	return firstName;
}

//the two following set name functions are for the two different overloaded constructor parameters
void customer::setlname(char* lname)
{
	if (strlen(lname) < 100)
		return;
	strcpy_s(lastName, lname);
}
void customer::setlname(string lname)
{
	if (lname.length() > 100)
		return;
	strcpy_s(lastName, lname.c_str());
}

//get name function for the last name
char* customer::getlname()
{
	return lastName;
}

//basic print function that displays the full name and ID
void customer::print()
{
	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "Customer ID: " << ID << endl;
	cout << endl;
}
