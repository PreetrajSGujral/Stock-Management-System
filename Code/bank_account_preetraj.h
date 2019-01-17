/*
NAME : preetraj 
DATE : 12/18/2017
PROJECT : ACCOUNT MANAGEMENT SYSTEM
FILE : DERIVED CLASS .H FILE
*/
#pragma once

#include<iostream>	// Standard I/O library
#include<fstream>	// File I/O library
#include<string>	// Standard string operations library
#include<time.h>	// Library for time stamp

using namespace std;
// include other class files
#include "account_preetraj.h"

#ifndef BANK_ACCOUNT_PREETRAJ_H
#define BANK_ACCOUNT_PREETRAJ_H

// Derived class BankAccount
class BankAccount : public Account
{
public:
	BankAccount();             // consructor
	~BankAccount();            // destructor

	virtual double getbal();	 // get cash balance
	virtual void setbal();		 // set cash balance

	void display_balance();         // view cash balance

	void cash_deposit(double);      // deposit cash
	void cash_withdraw(double);     // withdraw cash

	virtual void print_history();   // print history

private:
	
	ofstream file;
	ifstream read_file;

	ifstream balance_file;
	ofstream writebalance_file;

	string line;

	double deposit;
	double withdraw;

};

#endif
